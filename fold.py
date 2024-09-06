#!/usr/bin/env python
"""
fold.py : quick access to directory trees of NumPy .npy files eg created with NPFold.j
=========================================================================================

::

   In [1]: from np.fold import Fold
   In [2]: f = Fold(".")

From bash use "f"::

   f(){ ~/np/f.sh ;  }

"""

import os, sys, logging, numpy as np, datetime

try:
    import builtins
except ImportError:
    builtins = None
pass

from npmeta import NPMeta
#from opticks.sysrap.sframe import sframe

CMDLINE = " ".join(sys.argv)

log = logging.getLogger(__name__)
np.set_printoptions(suppress=True, edgeitems=5, linewidth=200,precision=3)


class STR(str):
    """STR inherits from str and changes the repr to provide the str : useful for interactive ipython"""
    def __repr__(self):
        return str(self)


def IsRemoteSession():
    """
    Heuristic to detect remote SSH session 
    """
    has_SSH_CLIENT = not os.environ.get("SSH_CLIENT", None) is None 
    has_SSH_TTY = not os.environ.get("SSH_TTY", None) is None 
    return has_SSH_CLIENT or has_SSH_TTY

class AttrBase(object):
    def __init__(self, symbol="t", prefix="", publish=False):
        self.__dict__["_symbol"] = symbol
        self.__dict__["_prefix"] = prefix
        self.__dict__["_publish"] = publish

    # name:str is only py3 ? 
    def __setattr__(self, name, value):           
        self.__dict__[name] = value
        key = "%s%s" % (self._prefix, name)
        if self._publish and not name.startswith("_"):
            print("publish key:%s " % key) 

            if not builtins is None: 
                setattr(builtins, key, value)
            pass
        pass
    pass
 
    def __repr__(self):
        lines = []
        for k,v in self.__dict__.items():
            line = k
            lines.append(line)
        pass 
        return "\n".join(lines)


class Fold(object):

    @classmethod
    def MultiLoad(cls, symbols=None):
        """
        Used by::

            CSG/tests/CSGSimtraceTest.py
            extg4/tests/X4SimtraceTest.py

        Values are read from the environment and added to the invoking global context
        using the builtins module. The prefixes are obtained from the SYMBOLS envvar 
        which defaults to "S,T".  

        Crucially in addition directory paths provided by S_FOLD and T_FOLD
        are loaded as folders and variables are added to global context. 

        The default SYMBOLS would transmogrify:

        * S_LABEL -> s_label 
        * T_LABEL -> t_label 
        * S_FOLD -> s 
        * T_FOLD -> t 

        In addition an array [s,t] is returned 
        """
        if symbols is None:
            symbols = os.environ.get("SYMBOLS", "S,T")
            if "," in symbols:
                symbols = symbols.split(",")
            else:
                symbols = list(symbols)
            pass
        pass
        print("symbols:%s " % str(symbols))
        ff = []
        for symbol in symbols:
            ekey = "$%s_FOLD" % symbol.upper() 
            label = os.environ.get("%s_LABEL" % symbol.upper(), None)
            setattr(builtins, "%s_label" % symbol.lower(), label)
            log.info("symbol %s ekey %s label %s " % (symbol,ekey, label)) 
            if not label is None:
                f = Fold.Load(ekey, symbol=symbol.lower() )
                ff.append(f)
            else:
                f = None 
            pass
            setattr(builtins, symbol.lower(), f)
            pass
        pass
        for f in ff:
            log.info(repr(f))
        pass
        return ff


    @classmethod
    def IsQuiet(cls, **kwa):
        quiet_default = True
        quiet = kwa.get("quiet", quiet_default) 
        return quiet 

    @classmethod
    def LoadConcat(cls, *args, **kwa0):
        kwa = kwa0.copy() 
        NEVT = kwa.pop("NEVT", 0) 
        log.info("LoadConcat NEVT %s " % NEVT) 
        ff = {}
        for evt in range(NEVT):
            kwa["evt"] = evt
            ff[evt] = cls.Load(*args, **kwa)
        pass
        fc = Fold.Concatenate(ff, **kwa0)
        fc.ff = ff 
        return fc

    @classmethod
    def Load(cls, *args, **kwa):
        """
        :param kwa: "parent=True" loads the parent folder  
        """
        reldir = kwa.pop("reldir", None) 
        parent = kwa.pop("parent", False) 
        evt = kwa.pop("evt", None) 

        if len(args) == 0:
            args = list(filter(None, [os.environ["FOLD"], reldir])) 
        pass


        relbase = os.path.join(*args[1:]) if len(args) > 1 else args[0]
        kwa["relbase"] = relbase   # relbase is the dir path excluding the first element 

        base = os.path.join(*args)
        base = os.path.expandvars(base) 
        quiet = cls.IsQuiet(**kwa)

        log.info("Fold.Load args %s quiet:%d" % (str(args), quiet))

        if not evt is None:
            base = base % evt 
        pass 
        ubase = os.path.dirname(base) if parent else base
        fold = cls(ubase, **kwa) if os.path.isdir(ubase) else None
        if fold is None:
            log.error("Fold.Load FAILED for base [%s]" % base )
        pass
        if quiet == False:
            print(repr(fold))
            print(str(fold))
        pass
        return fold

    def __getattr__(self, name):
        """Only called when there is no *name* attr"""
        return None


    SFRAME = "sframe.npy"
    INDEX = "NPFold_index.txt" 

    def brief(self):
        return "Fold : symbol %30s base %s " % (self.symbol, self.base) 

    @classmethod
    def IsFold(cls, base, name):
        """
        :param base:
        :param name:
        :return bool: True when indexpath:base/name/NPFold_index.txt exists
        """
        path = os.path.join(base, name)
        indexpath = os.path.join(path, cls.INDEX )
        return os.path.isdir(path) and os.path.exists(indexpath)

    def get_names(self, base):
        """
        :param base: directory path 
        :return names: list of names that are either .txt .npy or subfold
        """
        nn = os.listdir(base)
        if not self.order is None:
            sizes = list(map(lambda name:os.stat(os.path.join(base, name)).st_size, nn))
            order = np.argsort(np.array(sizes))
            if self.order == "descend":
                order = order[::-1] 
            pass
            nn = np.array(nn)[order]  
        pass

        names = []
        for n in nn:
            if n.endswith(".npy") or n.endswith(".txt"):
                names.append(n)
            elif self.IsFold(base,n):
                names.append(n)
            else:
                pass
            pass
        pass
        return names


    def __init__(self, base, **kwa):
        """
        Fold ctor
        """
        self.base = base
        self.kwa = kwa 
        self.quiet = self.IsQuiet(**kwa)
        self.symbol = kwa.get("symbol", "t")
        self.relbase = kwa.get("relbase")
        self.is_concat = kwa.get("is_concat", False)
        self.globals = kwa.get("globals", False) == True
        self.globals_prefix = kwa.get("globals_prefix", "") 
        self.order = kwa.get("order", None)
        assert self.order in ["ascend", "descend", None ] 

        if self.quiet == False:
            print(self.brief())
            print("Fold : setting globals %s globals_prefix %s " % (self.globals, self.globals_prefix)) 
        pass

        self.paths = []
        self.stems = []
        self.abbrev = []
        self.txts = {}

        if base is None or self.is_concat:
            log.info("not loading as base None or is_concat")
        else:
            self.load()
        pass


    def load(self):
        base = self.base
        symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        self.names = self.get_names(base)

        for i, name in enumerate(self.names):
            path = os.path.join(base, name)
            symbol = symbols[i]
            stem = name[:-4] if name.endswith(".npy") or name.endswith(".txt") else name

            self.paths.append(path)
            self.stems.append(stem)
            self.abbrev.append(symbol) 

            if name == self.SFRAME:
                a = None # sframe.Load(path)
            elif name.endswith(".npy"):
                a = np.load(path)
            elif name.endswith("_meta.txt"):
                a = NPMeta.Load(path)
                self.txts[name] = a 
            elif name.endswith(".txt"):
                a = NPMeta.LoadAsArray(path)
                self.txts[name] = a
            elif self.IsFold(base, name):
                a = Fold(path, symbol=name)
            pass
            setattr(self, stem, a ) 

            if self.globals:
                gstem = self.globals_prefix + stem
                setattr( builtins, gstem, a )
                setattr( builtins, symbol, a )
                print("setting builtins symbol:%s gstem:%s" % (symbol, gstem) ) 
            pass
        pass

    @classmethod
    def CommonNames(cls, ff):
        """
        Currently asserts that all Fold instances contain the same names and stems

        :param ff: dictionary holding Fold instances keyed by integers specifying order
        :return names, stems: two lists of common names and stems present in all Fold instances
        """
        names = []             
        stems = []
        for k,v in ff.items():
            if len(names) == 0:
                names = v.names
            else:
                assert names == v.names
            pass
            if len(stems) == 0:
                stems = v.stems
            else:
                assert stems == v.stems
            pass
        pass
        return names, stems


    @classmethod
    def BaseLabel(cls, base, shorten=False):
        """
        Example baselabel and shortened baselabel::

             /tmp/blyth/opticks/GEOM/R0J008/ntds2/ALL0/00[0,1,2,3,4,5,6,7,8,9]
             R0J008/ntds2/ALL0

        """
        label = "BaseLabel:unexpected-base-type"
        if type(base) is str:
            label = base
        elif type(base) is list:
            pfx = os.path.commonprefix(base) 
            tail = []
            for _ in base:
                tail.append(_[len(pfx):])
            pass
            label = "%s[%s]" % ( pfx, ",".join(tail)) 
        pass

        if shorten and "GEOM" in label:
            label = os.path.dirname(label.split("GEOM")[1][1:])    
        pass
        return label 

    @classmethod
    def Concatenate(cls, ff, **kwa0):
        """
        :param ff: dictionary holding Fold instances keyed by integers specifying order
        :return f: Fold instance created by concatenating the ff Fold arrays
        """
        kwa = kwa0.copy()
        kwa["is_concat"] = True 

        names, stems = cls.CommonNames(ff)
        assert len(names) == len(stems)
        kk = list(ff.keys())
        log.info("Concatenating %d Fold into one " % len(kk))
       
        bases = []
        for k in kk: 
            f = ff[k]
            bases.append(f.base)
        pass
        base = bases
        baselabel = cls.BaseLabel(bases) 

        fc = Fold(base, **kwa )
        fc.names = names
        fc.stems = stems 
        fc.paths = []
        for i in range(len(stems)):
            name = names[i]
            stem = stems[i]
            if name.endswith(".npy") and not stem == "sframe":
                aa = []
                for k in kk:
                    f = ff[k]
                    a = getattr(f, stem, None)
                    assert not a is None
                    aa.append(a)
                pass
                setattr(fc, stem, np.concatenate(tuple(aa)) )
            pass
        pass
        return fc 

    def _get_baselabel(self):
        return self.BaseLabel(self.base, shorten=True)

    baselabel = property(_get_baselabel)

    def desc(self):
        """
        for is_concat:True cannot assume there are .npy files 

        """
        now_stamp = datetime.datetime.now()
        l = []
        l.append(self.symbol)
        l.append("")
        l.append("CMDLINE:%s" % CMDLINE )
        l.append("%s.base:%s" % (self.symbol,self.base) )
        l.append("")
        stamps = []

        for i in range(len(self.stems)):
            stem = self.stems[i] 
            path = self.paths[i] if i < len(self.paths) else None
            abbrev = self.abbrev[i] if i < len(self.abbrev) else None
            abbrev_ = abbrev if self.globals else " " 
            aname = "%s.%s" % (self.symbol,stem)
            line = "%1s : %-50s :" % ( abbrev_, aname )

            a = getattr(self, stem)

            if a is None:
                line += " NO ATTR "
            else:
                kls = a.__class__.__name__
                ext = ".txt" if kls == 'NPMeta' else ".npy"
                name = "%s%s" % (stem,ext)

                sh = str(len(a)) if ext == ".txt" else str(a.shape)
                line += " %20s :" % ( sh )
            pass


            if not path is None and os.path.exists(path):
                st = os.stat(path)
                stamp = datetime.datetime.fromtimestamp(st.st_ctime)
                age_stamp = now_stamp - stamp
                stamps.append(stamp)
                line += " %s " % age_stamp
            else:
                line += " NO path " 
            pass
            l.append(line)
        pass
        l.append("")

        if len(stamps) > 0:
            min_stamp = min(stamps)
            max_stamp = max(stamps)
            dif_stamp = max_stamp - min_stamp 
            age_stamp = now_stamp - max_stamp
            l.append(" min_stamp : %s " % str(min_stamp))
            l.append(" max_stamp : %s " % str(max_stamp))
            l.append(" dif_stamp : %s " % str(dif_stamp))
            l.append(" age_stamp : %s " % str(age_stamp))
            assert dif_stamp.microseconds < 1e6, "stamp divergence detected microseconds %d : so are seeing mixed up results from multiple runs " % dif_stamp.microseconds 
        else:
            l.append("WARNING THERE ARE NO TIME STAMPS")
        pass
        return l 

    def __repr__(self):
        return "\n".join(self.desc())    

    def __str__(self):
        l = []
        for k in self.txts:
            l.append("")
            l.append(k)
            l.append("")
            l.append(str(self.txts[k]))
        pass
        return "\n".join(l) 
  

if __name__  == 'old__main__':
    pass
    logging.basicConfig(level=logging.INFO)
    NEVT = int(os.environ.get("NEVT",3))
    fc = Fold.LoadConcat(NEVT=NEVT, symbol="fc")
    print(repr(fc))

if __name__ == '__main__':
    f = Fold(".", symbol="f")                                                                                                     
    print(repr(f))



