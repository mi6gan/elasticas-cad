#include "elskirtdialogs.h"
namespace Elasticas
{
    SkirtPropertiesDialog::SkirtPropertiesDialog(const QString & name,const QString & garment_name): PropertiesDialog(name,garment_name)
    {

    }

    void SkirtPropertiesDialog::computeDarts()
    {
        const Elasticas::CommonData & var = Elasticas::Core::Instance()->commonVariables();
        int FrontDartsCount = var[ "StraightSkirt:FrontDartsCount" ].toInt();
        int SideDartsCount = var[ "StraightSkirt:SideDartsCount" ].toInt();
        int BackDartsCount = var[ "StraightSkirt:BackDartsCount" ].toInt();
        //Короткая инструкция
        //Для работы функции нужны переменные Т7, Т18, Т19, T46, T86, Р18, Р19.
        //Фунукция считает Spread (Раствор), Width (Растояние от линии симметрии) и Height (Длину)
        // для
        //Side1,
        //Front1,Front2,Front3
        //Back1,Back2,Back3
        //После расчета она записывает их в
        //Elasticas::CommonData var
        //с префиксом "Default"



        /*** HEADER ***/
        /*** INPUT ***/

        //Measures
        double T7 = var["T7"].toDouble() * 10;
                double T9 = var["T9"].toDouble() * 10;
        double T18 = var["T18"].toDouble() * 10;
        double T19 = var["T19"].toDouble() * 10;
        double P18 = this->commonValue("P18").toDouble() * 10;
        double P19 = this->commonValue("P19").toDouble() * 10;
        double T46 = var["T46"].toDouble() * 10;
        double T86 = var["T86"].toDouble() * 10;
        double Vyt = var["Vyt"].toDouble() * 10;

        double Width = T19 / 2 + P19;
        double WidthAtHipline = 0.5 * ( T19 - T18 ) + ( P19 - P18 ) ;
        double AB_f = T46 / 2 + 3;
        double AB_b = 0.4 * Width / 2;

        double a = T7 - T86;
            //a=T7-Vyt;


       /*** OUTPUT ***/

       double SideDart1Width, SideDart1Height, SideDart1Spread;

       double FrontDart1Width, FrontDart1Height, FrontDart1Spread;
       double FrontDart2Width, FrontDart2Height, FrontDart2Spread;
       double FrontDart3Width, FrontDart3Height, FrontDart3Spread;

       double BackDart1Width, BackDart1Height, BackDart1Spread;
       double BackDart2Width, BackDart2Height, BackDart2Spread;
       double BackDart3Width, BackDart3Height, BackDart3Spread;

       SideDart1Spread = 0;
       FrontDart1Spread = 0;
       FrontDart2Spread = 0;
       FrontDart3Spread = 0;
       BackDart1Spread = 0;
       BackDart2Spread = 0;
       BackDart3Spread = 0;

       SideDart1Height = 0;
       FrontDart1Height = 0;
       FrontDart2Height = 0;
       FrontDart3Height = 0;
       BackDart1Height = 0;
       BackDart2Height = 0;
       BackDart3Height = 0;

       SideDart1Width = 0;
       FrontDart1Width = 0;
       FrontDart2Width = 0;
       FrontDart3Width = 0;
       BackDart1Width = 0;
       BackDart2Width = 0;
       BackDart3Width = 0;

       /*** Header - end ***/

       /*** Math - start ***/

       if(FrontDartsCount==0) FrontDartsCount=1;
       if(BackDartsCount==0) BackDartsCount=1;
       switch ( FrontDartsCount )
       {
        case ( 0 ):
        switch ( BackDartsCount )
        {
         case ( 0 ):
                    SideDart1Spread = 0;
                    FrontDart1Spread = 0;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height = 0;
                    FrontDart1Height = 0;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = 0;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = 0;
                    FrontDart1Width = 0;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = 0;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
          break;
          case(1):
                    SideDart1Spread = 0.6;
                    FrontDart1Spread = 0;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.4;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height = a;
                    FrontDart1Height = 0;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = a * 0.8 - 10;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width / 2;
                    FrontDart1Width = 0;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
           break;
           case (2):
                    SideDart1Spread = 0.46;
                    FrontDart1Spread = 0;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.27;
                    BackDart2Spread = 0.27;
                    BackDart3Spread = 0;

                    SideDart1Height = a;
                    FrontDart1Height = 0;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height =  a*0.8-10;
                    BackDart2Height =  a*0.8-20;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = 0;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width /2 - SideDart1Spread*WidthAtHipline/2-AB_b)*0.5;
                    BackDart3Width = 0;
            break;
            case( 3 ):
                    SideDart1Spread = 0.4;
                    FrontDart1Spread = 0;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.2;
                    BackDart2Spread = 0.2;
                    BackDart3Spread = 0.2;

                    SideDart1Height = a;
                    FrontDart1Height = 0;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-20;
                    BackDart2Height =  a*0.8-20;
                    BackDart3Height = a*0.8-20;

                    SideDart1Width = Width/2;
                    FrontDart1Width = 0;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width/2-SideDart1Spread*WidthAtHipline/2-AB_b)*0.333;
                    BackDart3Width = AB_b+( Width/2-SideDart1Spread*WidthAtHipline/2-AB_b)*0.666;
                    break;
                }
                break;
            case(1):

                switch (BackDartsCount)
                {
                case (0):
                    SideDart1Spread = 0.6;
                    FrontDart1Spread = 0.4;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = 0;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width= Width-AB_f;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = 0;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(1):
                    SideDart1Spread = 0.5;
                    FrontDart1Spread = 0.18;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.32;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width= Width-AB_f;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case (2):
                    SideDart1Spread = 0.4;
                    FrontDart1Spread = 0.18;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.21;
                    BackDart2Spread = 0.21;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width/2-SideDart1Spread*WidthAtHipline/2-AB_b)*0.5;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(3):
                    SideDart1Spread = 0.4;
                    FrontDart1Spread = 0.18;
                    FrontDart2Spread = 0;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.14;
                    BackDart2Spread = 0.14;
                    BackDart3Spread = 0.14;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = 0;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-20;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = a*0.8-20;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width = 0;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width/2-SideDart1Spread*WidthAtHipline/2-AB_b)*0.333;
                    BackDart3Width = AB_b+( Width/2-SideDart1Spread*WidthAtHipline/2-AB_b)*0.666;


                    break;
                }

                break;
            case (2):

                switch (BackDartsCount)
                {
                case (0):
                    SideDart1Spread = 0.46;
                    FrontDart1Spread = 0.27;
                    FrontDart2Spread = 0.27;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = 0;
                    BackDart1Height = 0;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.5;
                    FrontDart3Width = 0;
                    BackDart1Width = 0;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(1):
                    SideDart1Spread = 0.48;
                    FrontDart1Spread = 0.10;
                    FrontDart2Spread = 0.10;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.32;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height = a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.5;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case (2):
                    SideDart1Spread = 0.38;
                    FrontDart1Spread = 0.10;
                    FrontDart2Spread = 0.10;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.21;
                    BackDart2Spread = 0.21;
                    BackDart3Spread = 0;

                    SideDart1Height = a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = 0;

                    SideDart1Width =  Width/2;
                    FrontDart1Width =  Width-AB_f;
                    FrontDart2Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.5;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width  /2 - SideDart1Spread*WidthAtHipline/2-AB_b)*0.5;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(3):
                    SideDart1Spread = 0.38;
                    FrontDart1Spread = 0.10;
                    FrontDart2Spread = 0.10;
                    FrontDart3Spread = 0;
                    BackDart1Spread = 0.14;
                    BackDart2Spread = 0.14;
                    BackDart3Spread = 0.14;

                    SideDart1Height = a;
                    FrontDart1Height = a*0.5-10;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = 0;
                    BackDart1Height = a*0.8-20;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = a*0.8-20;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.5;
                    FrontDart3Width = 0;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width  /2 - SideDart1Spread*WidthAtHipline/2-AB_b)*0.333;
                    BackDart3Width = AB_b+( Width  /2 - SideDart1Spread*WidthAtHipline/2-AB_b)*0.666;

                    //ok
                    break;
                }

                break;
            case(3):

                switch (BackDartsCount)
                {
                case (0):
                    SideDart1Spread = 0.4;
                    FrontDart1Spread = 0.2;
                    FrontDart2Spread = 0.2;
                    FrontDart3Spread = 0.2;
                    BackDart1Spread = 0;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-20;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = a*0.5-20;
                    BackDart1Height = 0;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.666;
                    FrontDart3Width =  Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.333;
                    BackDart1Width = 0;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(1):
                    SideDart1Spread = 0.48;
                    FrontDart1Spread = 0.0633;
                    FrontDart2Spread = 0.0633;
                    FrontDart3Spread = 0.0633;
                    BackDart1Spread = 0.32;
                    BackDart2Spread = 0;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-20;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = a*0.5-20;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = 0;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width = Width /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.666;
                    FrontDart3Width = Width /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.333;
                    BackDart1Width = AB_b;
                    BackDart2Width = 0;
                    BackDart3Width = 0;
                    //ok
                    break;
                case (2):

                    SideDart1Spread = 0.38;
                    FrontDart1Spread = 0.0633;
                    FrontDart2Spread = 0.0633;
                    FrontDart3Spread = 0.0633;
                    BackDart1Spread = 0.21;
                    BackDart2Spread = 0.21;
                    BackDart3Spread = 0;

                    SideDart1Height= a;
                    FrontDart1Height = a*0.5-20;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = a*0.5-20;
                    BackDart1Height = a*0.8-10;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = 0;

                    SideDart1Width = Width/2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width = Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.666;
                    FrontDart3Width = Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.333;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width  /2-AB_b - SideDart1Spread*WidthAtHipline/2)*0.5;
                    BackDart3Width = 0;
                    //ok
                    break;
                case(3):
                    SideDart1Spread = 0.38;
                    FrontDart1Spread = 0.0633;
                    FrontDart2Spread = 0.0633;
                    FrontDart3Spread = 0.0633;
                    BackDart1Spread = 0.14;
                    BackDart2Spread = 0.14;
                    BackDart3Spread = 0.14;

                    SideDart1Height = a;
                    FrontDart1Height = a*0.5-20;
                    FrontDart2Height = a*0.5-20;
                    FrontDart3Height = a*0.5-20;
                    BackDart1Height = a*0.8-20;
                    BackDart2Height = a*0.8-20;
                    BackDart3Height = a*0.8-20;

                    SideDart1Width = Width  /2;
                    FrontDart1Width = Width-AB_f;
                    FrontDart2Width = Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.666;
                    FrontDart3Width = Width  /2+ SideDart1Spread*WidthAtHipline/2 + ( FrontDart1Width  - Width  /2 - SideDart1Spread*WidthAtHipline/2)*0.333;
                    BackDart1Width = AB_b;
                    BackDart2Width = AB_b+( Width  /2-AB_b - SideDart1Spread*WidthAtHipline/2)*0.333;
                    BackDart3Width = AB_b+( Width  /2-AB_b - SideDart1Spread*WidthAtHipline/2)*0.666;
           break;
          }
          break;
         }


         SideDart1Spread *= WidthAtHipline;
         FrontDart1Spread *= WidthAtHipline;
         FrontDart2Spread *= WidthAtHipline;
         FrontDart3Spread *= WidthAtHipline;
         BackDart1Spread *= WidthAtHipline;
         BackDart2Spread *= WidthAtHipline;
         BackDart3Spread *= WidthAtHipline;

         /***                                                       MATH:END                                                     ***/


         /***               Now calculated values will be set as ones by default                ***/

        this->commonValue("SideDarts0Spread" ) = SideDart1Spread / 10;
        this->commonValue("SideDarts0Width") = SideDart1Width / 10;
        this->commonValue("SideDarts0Height") = SideDart1Height / 10;

        this->commonValue("FrontDarts0Spread") = FrontDart1Spread / 10;
        this->commonValue("FrontDarts0Width") = FrontDart1Width / 10;
        this->commonValue("FrontDarts0Height") = FrontDart1Height / 10;
        this->commonValue("FrontDarts1Spread" ) = FrontDart2Spread / 10;
        this->commonValue("FrontDarts1Width" ) = FrontDart2Width / 10;
        this->commonValue("FrontDarts1Height" ) = FrontDart2Height / 10;
        this->commonValue("FrontDarts2Spread" ) = FrontDart3Spread / 10;
        this->commonValue("FrontDarts2Width" ) = FrontDart3Width / 10;
        this->commonValue("FrontDarts2Height" ) = FrontDart3Height / 10;

        this->commonValue("BackDarts0Spread" ) = BackDart1Spread / 10;
        this->commonValue("BackDarts0Width" ) = BackDart1Width / 10;
        this->commonValue("BackDarts0Height" ) = BackDart1Height / 10;
        this->commonValue("BackDarts1Spread" ) = BackDart2Spread / 10;
        this->commonValue("BackDarts1Width" ) = BackDart2Width / 10;
        this->commonValue("BackDarts1Height" ) = BackDart2Height / 10;
        this->commonValue("BackDarts2Spread" ) = BackDart3Spread / 10;
        this->commonValue("BackDarts2Width" ) = BackDart3Width / 10;
        this->commonValue("BackDarts2Height" ) = BackDart3Height / 10;
    }

    void SkirtPropertiesDialog::exec()
    {
        this->computeDarts();
        PropertiesDialog::exec();
    }

    void SkirtPropertiesDialog::InitSkirtBKBasicProperties()
    {
        double T7=Core::Instance()->commonVariables()["T7"].toDouble();
        double T9=Core::Instance()->commonVariables()["T9"].toDouble();
        double T1=Core::Instance()->commonVariables()["T1"].toDouble();
        double T16=Core::Instance()->commonVariables()["T16"].toDouble();
        double T19=Core::Instance()->commonVariables()["T19"].toDouble();
        double Vps=-24.894073+0.626460*T1+0.071291*T16-0.100910*T19;
        this->commonValue("A1:Default")=T7-T9+5.0; //Длина юбки
        this->commonValue("A1:Min")=T7-Vps; //Длина юбки
        this->commonValue("A1:Max")=T7-10.0; //Длина юбки
        this->commonValue("BeltZipperLength:Min")=(T19-T16)/2.0; //Длина юбки
        this->commonValue("BeltZipperLength:Max")=100.0f; //Длина юбки
        this->commonValue("SideDartsCount")=1;
        this->commonValue("FrontDartsCount")=1;
        this->commonValue("BackDartsCount")=1;

        this->commonValue("P18:Default")=0.5f; //Прибавка к обхвату талии
        this->commonValue("P18:Min")=-3.0f;
        this->commonValue("P18:Max")=10.0f;
        this->commonValue("P19:Default")=1.0f; // Прибавка к обхвату бёдер
        this->commonValue("P19:Min")=-3.0f;
        this->commonValue("P19:Max")=10.0f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к полуобхвату талии (см)"),"P18",0.1f);
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к полуобхвату бёдер (см)"),"P19",0.1f);
        this->AddDoubleSpinBoxProperty(trUtf8("Длина юбки (см)"),"A1");
        this->InitSkirtDressPT();
        /*

        this->commonValue("Sleeve:Default")=false;
        this->AddCheckBoxProperty(trUtf8("С рукавом"),"Sleeve");
        this->commonValue("HorizPart:Default")=false;
        this->AddCheckBoxProperty(trUtf8("С горизонтальным членением"),"HorizPart");*/
    }

    void SkirtPropertiesDialog::InitSkirtIMKBeltProperties()
    {
        this->commonValue("Belt:Default")=1; // Тип пояса
        this->commonValue("BeltWithRubber:Default")=false; // Пояс с резинкой
        this->commonValue("BeltWidth:Default")=3.0f; // Ширина пояса
        this->commonValue("BeltWidth:Min")=0.0f;
        this->commonValue("BeltWidth:Max")=4.0f;
        this->commonValue("RubberP:Default")=0.0f;
        this->commonValue("RubberP:Min")=0.0f;
        this->commonValue("RubberP:Max")=100.0f;

        ComboBoxProperty* cmbp1;
        CheckBoxProperty* cbp1;
        AbstractProperty* p1;

        const QString belt_type_names[]={trUtf8("Без пояса"),trUtf8("Притачной"),trUtf8("Цельновыкроенный"),NULL};
        const CommonData & vars=Core::Instance()->CommonVariables();
        cmbp1=this->AddComboBoxProperty(trUtf8("Тип пояса"),belt_type_names,"Belt");

        cbp1=this->AddCheckBoxProperty(trUtf8("Пояс с резинкой"),"BeltWithRubber");
        cbp1->AddCondition(new ComboBoxCondition(cmbp1,0),OperationAndNot);

        p1=this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к обхвату талии для резинки (см)"),"RubberP",0.1f);
        p1->AddCondition(new CheckBoxCondition(cbp1,true),OperationAnd);

        p1=this->AddDoubleSpinBoxProperty(trUtf8("Ширина пояса (см)"),"BeltWidth",0.1f);
        p1->AddCondition(new ComboBoxCondition(cmbp1,0),OperationAndNot);
    }

    void SkirtPropertiesDialog::InitSkirtIMKClaspProperties(bool are_sews_optional)
    {
        this->commonValue("BeltLedgeWidth:Default")=3.0f;
        this->commonValue("ZippetAtBeltEnd:Default")=false;
        this->commonValue("BeltZipperLength:Default")=18.0f;

        AbstractProperty* p1;
        CheckBoxProperty* cbp1;
        ComboBoxProperty* cmbp1,*cmbp2;
        ComboBoxProperty::Item * cmbp1_item[4];
        const CommonData & vars=Core::Instance()->CommonVariables();
        this->AddProperty(cbp1=new CheckBoxProperty(trUtf8("Застёжка"),true),"Clasp");
        this->AddProperty(cmbp1=new ComboBoxProperty(trUtf8("Расположение")),"ClaspPosition");
        cmbp1_item[0]=cmbp1->AddItem(trUtf8("В левом боковом шве"));
        cmbp1_item[1]=cmbp1->AddItem(trUtf8("В правом боковом шве"));
        cmbp1_item[2]=cmbp1->AddItem(trUtf8("В шве спереди"));
        cmbp1_item[3]=cmbp1->AddItem(trUtf8("В шве сзади"));
        if(are_sews_optional)
        {
            cmbp1_item[0]->AddCondition(new CheckBoxCondition((CheckBoxProperty*)
                                                        global_var_names_to_properties[this->dialogClass()->className()]["VB"],true));
            cmbp1_item[1]->AddCondition(new CheckBoxCondition((CheckBoxProperty*)
                                                        global_var_names_to_properties[this->dialogClass()->className()]["VB"],true));
            cmbp1_item[2]->AddCondition(new CheckBoxCondition((CheckBoxProperty*)
                                                        global_var_names_to_properties[this->dialogClass()->className()]["VP"],true));
            cmbp1_item[3]->AddCondition(new CheckBoxCondition((CheckBoxProperty*)
                                                       global_var_names_to_properties[this->dialogClass()->className()]["VZ"],true));
        }
        cmbp1->AddCondition(new CheckBoxCondition(cbp1,true));

        this->AddProperty(cmbp1=new ComboBoxProperty(trUtf8("Вид застёжки")),"ClaspType");
        cmbp1->AddItem(trUtf8("Молния"));
        cmbp1->AddItem(trUtf8("Пуговицы"));
        cmbp1->AddCondition(new CheckBoxCondition(cbp1,true));


        this->AddProperty(cbp1=new CheckBoxProperty(trUtf8("Молния до конца пояса"),true),"ZipperAtBeltEnd");
        cbp1->AddCondition(new ComboBoxCondition(cmbp1,0),OperationAnd,false);
        cbp1->AddCondition(new ComboBoxCondition((ComboBoxProperty*)
                                               global_var_names_to_properties[this->dialogClass()->className()]["Belt"],0),OperationAndNot);



        this->AddProperty(p1=new DoubleSpinBoxProperty(trUtf8("Ширина уступа пояса (см)"),
                                                    vars[this->dialogClass()->className()+":BeltLedgeWidth:Default"].toDouble(),
                                                    0.0f,100.0f),"BeltLedgeWidth");
        p1->AddCondition(new CheckBoxCondition(cbp1,false));

        this->AddProperty(p1=new DoubleSpinBoxProperty(trUtf8("Длина молнии (см)"),
                                                    vars[this->dialogClass()->className()+":BeltZipperLength:Default"].toDouble(),
                                                    0.0f,100.0f),"BeltZipperLength");
        p1->AddCondition(new ComboBoxCondition(cmbp1,0));

        this->AddProperty(p1=new DoubleSpinBoxProperty(trUtf8("Диаметр пуговиц (см)"),0.0f,0.0f,100.0f));
        p1->AddCondition(new ComboBoxCondition(cmbp1,1));

        this->AddProperty(p1=new DoubleSpinBoxProperty(trUtf8("Ширина застёжки (см)"),3.0f,0.0f,100.0f));
        p1->AddCondition(new ComboBoxCondition(cmbp1,1));

        this->AddProperty(p1=new SpinBoxProperty(trUtf8("Количество пуговиц"),3,1,100));
        p1->AddCondition(new ComboBoxCondition(cmbp1,1));

        this->AddProperty(cmbp2=new ComboBoxProperty(trUtf8("Сквозная или закрытая")));
        cmbp2->AddItem(trUtf8("Сквозная"));
        cmbp2->AddItem(trUtf8("Закрытая"));
        cmbp2->AddCondition(new ComboBoxCondition(cmbp1,1));
    }

    SkirtDebugDialog::SkirtDebugDialog(const QString & name,const QString & class_name):PropertiesDialog(name,class_name)
    {
        this->AddDoubleSpinBoxProperty(trUtf8("Верхняя прибавка к середине\nюбки на виде спереди"),"tmp0",0.1f,-100.0f,100.0f);
        this->AddDoubleSpinBoxProperty(trUtf8("Нижняя прибавка к середине\nюбки на виде спереди"),"tmp1",0.1f,-100.0f,100.0f);
        this->AddDoubleSpinBoxProperty(trUtf8("Верхняя передняя прибавка к середине\nюбки на виде сбоку"),"tmp3",0.1f,-100.0f,100.0f);
        this->AddDoubleSpinBoxProperty(trUtf8("Нижняя передняя прибавка к середине\nюбки на виде сбоку"),"tmp4",0.1f,-100.0f,100.0f);
        this->AddDoubleSpinBoxProperty(trUtf8("Верхняя задняя прибавка к середине\nюбки на виде сбоку"),"tmp5",0.1f,-100.0f,100.0f);
        this->AddDoubleSpinBoxProperty(trUtf8("Нижняя задняя прибавка к середине\nюбки на виде сбоку"),"tmp6",0.1f,-100.0f,100.0f);
        //this->AddDoubleSpinBoxProperty(trUtf8("Ширина пояса по низу"),"tmp2",0.1f,0.0f,100.0f);
    }
//_________________________________________________-
    BlouseDebugDialog::BlouseDebugDialog(const QString & name,const QString & class_name):PropertiesDialog(name,class_name)
    {
        this->commonValue("sleeve_bk_1:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сзади 1"),"sleeve_bk_1");
        this->commonValue("sleeve_bk_2:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сзади 2"),"sleeve_bk_2");
        this->commonValue("sleeve_bk_3:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сзади 3"),"sleeve_bk_3");
        this->commonValue("sleeve_bk_4:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сзади 4"),"sleeve_bk_4");
        this->commonValue("sleeve_sd_1:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сбоку 1"),"sleeve_sd_1");
        this->commonValue("sleeve_sd_2:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сбоку 2"),"sleeve_sd_2");
        this->commonValue("sleeve_sd_3:Default")=0.1f;
        this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к рукаву сбоку 3"),"sleeve_sd_3");
        this->commonValue("sleeve_sd_3:Default")=40.0f;
        //this->AddDoubleSpinBoxProperty(trUtf8("Длина рукава"),"sleeve_length_3");
        //this->AddCheckBoxProperty(trUtf8("Манжет"),"CuffsOn");
    }

}
