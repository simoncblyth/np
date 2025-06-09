#include "NPX.h"
#include "NPFold.h"

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


int main(int argc, char** argv)
{
    NP* th = NPX::FromNumpyString<double>(DOUBLE_STR) ;

    bool reverse = true ;
    NP* ct = NP::MakeWithCosineDomain(th, reverse);

    int ni = 91 ;

    NP* theta = NP::ThetaRadians<double>(ni,0.5) ;  // 0.:pi/2
    NP* costh = NP::Cos(theta) ;

    const double* tt = theta->cvalues<double>();
    const double* cc = costh->cvalues<double>();

    int nj = 3 ;
    NP* re = NP::Make<double>( ni, nj );
    double* rr = re->values<double>();
    for(int i=0 ; i < ni ; i++ )
    {
        double th_interp = th->interp( tt[i] ) ;
        double ct_interp = ct->interp( cc[i] ) ;

        rr[nj*i+0] = th_interp ;
        rr[nj*i+1] = ct_interp ;
        rr[nj*i+2] = th_interp - ct_interp ;
    }


    NPFold* fold = new NPFold ;
    fold->add("theta", theta);
    fold->add("costh", costh);
    fold->add("th", th);
    fold->add("ct", ct);
    fold->add("re", re);

    fold->save("$FOLD/MakeWithCosineDomain" );
    return 0 ;
}

