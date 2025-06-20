

#include "NPX.h"
#include "NPFold.h"

const char* INT64_STR = R"LITERAL(
array([[    0,   209,   223,   265,   265,   489,   505,   522,   723,  2097,  2097, 63816, 63919],
       [    0,   231,   244,   284,   284,   285,   368,   394,   590,   633,   633, 57248, 57356],
       [    0,   233,   245,   285,   285,   286,   351,   380,   638,   681,   681, 57402, 57480],
       [    0,   133,   170,   173,   173,   175,   259,   305,   844, 30887, 30888, 60904, 60961],
       [    0,   187,   226,   229,   230,   232,   396,   471,  1188, 33499, 33500, 63340, 63406],
       [    0,   170,   210,   214,   215,   217,   294,   328,   634, 31164, 31164, 60558, 60630],
       [    0,   131,   171,   174,   175,   177,   237,   273,   570, 32739, 32740, 62156, 62219],
       [    0,   136,   175,   179,   179,   181,   242,   292,   827, 32244, 32244, 62329, 62389],
       [    0,   135,   175,   179,   179,   181,   247,   281,   597, 32904, 32904, 62951, 63012],
       [    0,   132,   170,   174,   175,   177,   237,   271,   565, 32285, 32285, 62043, 62105]])
)LITERAL" ;


const char* INT32_STR = R"LITERAL(
array([[    0,   209,   223,   265,   265,   489,   505,   522,   723,  2097,  2097, 63816, 63919],
       [    0,   231,   244,   284,   284,   285,   368,   394,   590,   633,   633, 57248, 57356],
       [    0,   233,   245,   285,   285,   286,   351,   380,   638,   681,   681, 57402, 57480],
       [    0,   133,   170,   173,   173,   175,   259,   305,   844, 30887, 30888, 60904, 60961],
       [    0,   187,   226,   229,   230,   232,   396,   471,  1188, 33499, 33500, 63340, 63406],
       [    0,   170,   210,   214,   215,   217,   294,   328,   634, 31164, 31164, 60558, 60630],
       [    0,   131,   171,   174,   175,   177,   237,   273,   570, 32739, 32740, 62156, 62219],
       [    0,   136,   175,   179,   179,   181,   242,   292,   827, 32244, 32244, 62329, 62389],
       [    0,   135,   175,   179,   179,   181,   247,   281,   597, 32904, 32904, 62951, 63012],
       [    0,   132,   170,   174,   175,   177,   237,   271,   565, 32285, 32285, 62043, 62105]], dtype=int32)
)LITERAL" ;


const char* DOUBLE_STR = R"LITERAL(
array([[0.      , 0.911   ],
       [0.226893, 0.911   ],
       [0.488692, 0.9222  ],
       [0.715585, 0.9294  ],
       [0.959931, 0.9235  ],
       [1.151917, 0.93    ],
       [1.37881 , 0.9095  ],
       [1.48353 , 0.6261  ],
       [1.570796, 0.2733  ]])
)LITERAL" ;

const char* FLOAT_STR = R"LITERAL(
array([[0.      , 0.911   ],
       [0.226893, 0.911   ],
       [0.488692, 0.9222  ],
       [0.715585, 0.9294  ],
       [0.959931, 0.9235  ],
       [1.151917, 0.93    ],
       [1.37881 , 0.9095  ],
       [1.48353 , 0.6261  ],
       [1.570796, 0.2733  ]] dtype=float32)
)LITERAL" ;


int test_FromNumpyString()
{
    NPFold* fold = new NPFold ;

    bool dump = false ;
    //bool dump = true ;

    NP* i32 = NPX::FromNumpyString<int32_t>(INT32_STR, dump) ;
    std::cout << " i32 " << ( i32 ? i32->sstr() : "-" ) << std::endl ;
    fold->add("i32", i32);

    NP* i64 = NPX::FromNumpyString<int64_t>(INT64_STR, dump) ;
    std::cout << " i64 " << ( i64 ? i64->sstr() : "-" ) << std::endl ;
    fold->add("i64", i64);

    NP* d = NPX::FromNumpyString<double>(DOUBLE_STR, dump) ;
    std::cout << " d " << ( d ? d->sstr() : "-" ) << std::endl ;
    fold->add("d", d);

    NP* f = NPX::FromNumpyString<float>(FLOAT_STR, dump) ;
    std::cout << " f " << ( f ? f->sstr() : "-" ) << std::endl ;
    fold->add("f", f);

    fold->save("$FOLD/FromNumpyString");

    return 0 ;
}

int main()
{
    const char* TEST = U::GetEnv("TEST", "FromNumpyString") ;
    bool ALL = 0==strcmp("ALL", TEST) ;

    int rc = 0 ;
    if(ALL||0==strcmp(TEST, "FromNumpyString")) rc += test_FromNumpyString();

    return rc ;
}
