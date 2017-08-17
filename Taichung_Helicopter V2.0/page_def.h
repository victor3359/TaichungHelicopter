#ifndef PAGE_DEF_H
#define PAGE_DEF_H
#include <QString>

typedef enum
{
    IDX_Page1,
    IDX_Page2,
    START_Page1,
    START_Page2,
    COM_Page1,
    COM_Page2,
    MDL_Page1,
    MDL_Page2,
    MDL_Error
}PageIdx;


typedef struct PageData{
    QString DataLine1;
    QString TitleLine;
    QString DataLine3;
    QString InformationLine;
    QString DataLine5;
    QString AnnunciatorLine;
    QString DataLine7;
    QString ScratchPAD;
}PageData;

class Page_Def
{
public:
    Page_Def();
    PageIdx getPage();
    PageData gotoPage(PageIdx state);
private:
    PageIdx states;
};


#endif // PAGE_DEF_H
