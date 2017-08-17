#include "page_def.h"


static PageData pagedata;

Page_Def::Page_Def()
{
    this->states = IDX_Page1;
    gotoPage(this->states);
}

PageIdx Page_Def::getPage(){
    return this->states;
}

PageData Page_Def::gotoPage(PageIdx state){
    this->states = state;
    switch(states){
    case IDX_Page1:
        pagedata.DataLine1 = "<-START\t\t       ZEROIZE->";
        pagedata.TitleLine = "INDEX 1/2";
        pagedata.DataLine3 = "<-ROUTES\t\t    PATTERNS->";
        pagedata.InformationLine = "";
        pagedata.DataLine5 = "<-TGT LIST\t\tWPT LIST->";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "<-TIMERS\t\t          POWER->";
        pagedata.ScratchPAD = "";
        return pagedata;
    case IDX_Page2:
        pagedata.DataLine1 = "<-PIM\t\t\t\t\t\t\t";
        pagedata.TitleLine = "INDEX 2/2";
        pagedata.DataLine3 = "";
        pagedata.InformationLine = "";
        pagedata.DataLine5 = "";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "";
        pagedata.ScratchPAD = "";
        return pagedata;
    case START_Page1:
        pagedata.DataLine1 = "<-WGS -84\t\t\t\t\t\t";
        pagedata.TitleLine = "START 1/2";
        pagedata.DataLine3 = "[N285322.5\t  W0705325.4]";
        pagedata.InformationLine = "MM/DD/YY\t\tHHMM:SSZ";
        pagedata.DataLine5 = "[01/01/80]\t\t[0000:00Z]";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "BAROALT[\t0]\t\tMDL->";
        pagedata.ScratchPAD = "";
        return pagedata;
    case START_Page2:
        pagedata.DataLine1 = "SP EDIT:\t\tON\t\t\t";
        pagedata.TitleLine = "START 2/2";
        pagedata.DataLine3 = "SP AUTO FILL: ON\t\t";
        pagedata.InformationLine = "";
        pagedata.DataLine5 = "<-IDM QUICK SETUP\t\t";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "";
        pagedata.ScratchPAD = "";
        return pagedata;
    case MDL_Page1:
        pagedata.DataLine1 = "-> LOAD\t\t\t\t\t\t";
        pagedata.TitleLine = "MDL PAGE";
        pagedata.DataLine3 = "CCS MANGO\t\t10/23/03";
        pagedata.InformationLine = "";
        pagedata.DataLine5 = "TIME LEFT:\t\t16:21:31";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "";
        pagedata.ScratchPAD = "";
        return pagedata;
    case MDL_Page2:
        pagedata.DataLine1 = "* LOAD\t\t\tCANCEL <-";
        pagedata.TitleLine = "MDL PAGE";
        pagedata.DataLine3 = "CSS MANGO\t\t 12/01/03*";
        pagedata.InformationLine = "MDL TANGO\t\t12/02/03 ";
        pagedata.DataLine5 = "CONFIG ID AH1W 0001";
        pagedata.AnnunciatorLine = "TARGET 21";
        pagedata.DataLine7 = "<- ERRS XX\t\t\t\t\t";
        pagedata.ScratchPAD = "";
        return pagedata;
    case MDL_Error:
        pagedata.DataLine1 = "";
        pagedata.TitleLine = "SOURCE\tERRORS\tTYPE";
        pagedata.DataLine3 = "";
        pagedata.InformationLine = "";
        pagedata.DataLine5 = "";
        pagedata.AnnunciatorLine = "";
        pagedata.DataLine7 = "";
        pagedata.ScratchPAD = "";
        return pagedata;
    default:
        break;
    }
}
