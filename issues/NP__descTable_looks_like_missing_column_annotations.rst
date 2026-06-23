issues/NP__descTable_looks_like_missing_column_annotations.rst
===============================================================

Overview
--------


* descTable text represention missing parts


Issues - FIXED TRIVIALLY - WAS JUST SOME POOR IMPL
-----------------------------------------------------

* unlabelled last column
* missing columns in the key



Symptom
-------
::

    [lo] A[blyth@localhost tests]$ sreport__CONFIG=submeta cxs_min.sh report
    /data1/blyth/local/opticks_Debug/bin/cxs_min.sh - Internal GEOM setup detected
    [sreport.main CONFIG [submeta] argv0 sreport dirp /data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first is_executable_sibling_path NO 
    [sreport_Creator.desc
    [sreport_Creator.desc_fold
    fold = NPFold::LoadNoData("/data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first")
    fold YES
    fold_valid YES
    ]sreport_Creator.desc_fold
    ]sreport_Creator.desc
    [sreport.desc CONFIG[submeta]
    [sreport.desc_submeta {submeta for profiling info is replaced by *ranges* which just needs SProf.txt - not full SEvt saving} 

     a (2, 16, )
     b (0, )
    [NP::descTable_ {} (2, 16, )
                           index     SbOE0     SbOE1     SeOE0      tBOE      tsG3      tsG4      tsG5      tsG6      tsG7      tsG8      tPrL      tPoL      tEOE   t_Event  t_Launch
                //A000         0  0.000000  0.000125  0.329691  0.000013  0.000193  0.000392  0.000408  0.000426  0.001612  0.014091  0.014138  0.311365  0.329699    329686         0  0.018334            //A000 
                //A001         1  0.396281  0.396337  0.710872  0.396288  0.396378  0.396378  0.396396  0.396406  0.397249  0.397254  0.397264  0.690045  0.710878    314590         0  0.020833            //A001 
    num_timestamp 26 auto-offset from t0 1782097509501642
                TOTAL:         1    396281    396462   1040563    396301    396571    396770    396804    396832    398861    411345    411402   1001410   1040577    644276         0
        SbOE0 : SEvt__beginOfEvent_0
        SbOE1 : SEvt__beginOfEvent_1
        SeOE0 : SEvt__endOfEvent_0
         tBOE : t_BeginOfEvent
         tsG3 : t_setGenstep_3
         tsG4 : t_setGenstep_4
         tsG5 : t_setGenstep_5
         tsG6 : t_setGenstep_6
         tsG7 : t_setGenstep_7
         tsG8 : t_setGenstep_8
         tPrL : t_PreLaunch
         tPoL : t_PostLaunch
         tEOE : t_EndOfEvent
    ]NP::descTable_ {} (2, 16, )

    [NP::descTable_ {} (0, )
     ERROR : UNEXPECTED SHAPE ndim 1
     column_labels 
     row_labels 
    ]NP::descTable_ {} (0, )

    ]sreport.desc_submeta
    ]sreport.desc
    NPFold::save("$SREPORT_FOLD")
     resolved to  [/data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first_sreport]
    ]sreport.main



Look at NumPy level
---------------------

::

    cd /data1/blyth/tmp/GEOM/J26_1_1_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_medium_scan_first_sreport
    
    In [2]: f.submeta.a_names
    Out[2]: array(['//A000', '//A001'], dtype='<U6')

    In [6]: f.submeta.a_labels.reshape(-1,1)
    Out[6]: 
    array([['index'],

       ['SEvt__beginOfEvent_0'],
       ['SEvt__beginOfEvent_1'],
       ['SEvt__endOfEvent_0'],
       ['t_BeginOfEvent'],
       ['t_setGenstep_3'],
       ['t_setGenstep_4'],
       ['t_setGenstep_5'],
       ['t_setGenstep_6'],
       ['t_setGenstep_7'],
       ['t_setGenstep_8'],
       ['t_PreLaunch'],
       ['t_PostLaunch'],
       ['t_EndOfEvent'],

       ['t_Event'],
       ['t_Launch']], dtype='<U20')

    In [7]: f.submeta.a.shape
    Out[7]: (2, 16)





