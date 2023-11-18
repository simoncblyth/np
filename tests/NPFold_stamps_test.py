#!/usr/bin/env python

import numpy as np
from np.fold import Fold 
MODE =  int(os.environ.get("MODE", "2"))

if MODE != 0:
    from opticks.ana.pvplt import * 
    WM = mp.pyplot.get_current_fig_manager()  
else:
    WM = None
pass




labels_ = lambda f:f.labels.view("|S%d" % f.labels.shape[1])[:,0]  
delta_  = lambda s:np.diff(s, axis=1 )
tv_ = lambda a:a.view("datetime64[us]")  


if __name__ == '__main__':
    pn = Fold.Load(symbol="pn")
    print(repr(pn))
    n = pn.n 
    p = pn.p 
    plabel = " ".join(p.stamps_meta) 

    #ns = n.stamps
    #dns = ns[:,-1]-ns[:,2]  ## maybe that includes the above in mode:3 
    #nl = labels_(n)[:1] 
    #nd = delta_(n)
    #ntab = np.c_[nl, nd.T ]   
    #print(ntab)
    #fac = dns/dps  

    ps = p.stamps
    dps = ps[:,-1]-ps[:,2]  ## t_BeginOfEvent -> t_EndOfEvent
    _pl = labels_(p)

    pss =  p.stamps[1:,2:] # skip 1st event and first 2 stamps (init, BeginOfRun) 

    pd = np.diff( pss, axis=1 )  
    pl = _pl[3:]                # 3 as the diff removes 1 
    assert len(pl) == pd.shape[1]

    pp = p.stamps_names[1:]   
    assert len(pp) == pd.shape[0]

    ptab = np.c_[pl, pd.T ]   
    print(ptab)

    label = "NPFold_stamps_test "
    label += plabel

    if MODE == 2:
        fig, axs = mpplt_plotter(nrows=1, ncols=1, label=label, equal=False)
        ax = axs[0]

        

        

    pass    
    




