#include "mainwindow.h"
#include "ui_mainwindow.h"

static PageData pagedata;
static PageIdx state;
static int spidx = 0;

unsigned char COM[COM_COUNT] = {COM17, COM16, COM15, COM14,
                                COM04, COM03, COM02, COM01};
unsigned char PIN[PIN_COUNT] = {PIN05, PIN06, PIN07, PIN24,
                                PIN25, PIN26, PIN27, PIN28, PIN29};
short i, j;
void InitWiring(){
    wiringPiSetupGpio();
    for(i=0;i<COM_COUNT;i++){
        pinMode(COM[i], OUTPUT);
        digitalWrite(COM[i], LOW);
    }
    for(i=0;i<PIN_COUNT;i++){
        pinMode(PIN[i], INPUT);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    InitWiring();

    state = pagedef.getPage();
    pagedata = pagedef.gotoPage(state);
    setText();

    timer = new QTimer(this);
    timer->start(20);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(HoliLoop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTextsp(QString sp){
    pagedata.ScratchPAD.insert(spidx++, sp);
    ui->txt_sp->setText(pagedata.ScratchPAD);
    ui->txt_sp->setAlignment(Qt::AlignCenter);
}

void MainWindow::setTextbs(){
    pagedata.ScratchPAD.chop(1);
    spidx--;
    ui->txt_sp->setText(pagedata.ScratchPAD);
    ui->txt_sp->setAlignment(Qt::AlignCenter);
}

void MainWindow::setText(){
    //SetText
    spidx = 0;
    ui->txt_DL1->setText(pagedata.DataLine1);
    ui->txt_Title->setText(pagedata.TitleLine);
    ui->txt_DL3->setText(pagedata.DataLine3);
    ui->txt_Info->setText(pagedata.InformationLine);
    ui->txt_DL5->setText(pagedata.DataLine5);
    ui->txt_AnL->setText(pagedata.AnnunciatorLine);
    ui->txt_DL7->setText(pagedata.DataLine7);
    ui->txt_sp->setText(pagedata.ScratchPAD);
    //SetAlignment
    ui->txt_DL1->setAlignment(Qt::AlignCenter);
    ui->txt_Title->setAlignment(Qt::AlignCenter);
    ui->txt_DL3->setAlignment(Qt::AlignCenter);
    ui->txt_Info->setAlignment(Qt::AlignCenter);
    ui->txt_DL5->setAlignment(Qt::AlignCenter);
    ui->txt_AnL->setAlignment(Qt::AlignCenter);
    ui->txt_DL7->setAlignment(Qt::AlignCenter);
    ui->txt_sp->setAlignment(Qt::AlignCenter);
}

void MainWindow::clearText(){
    pagedata.ScratchPAD = "";
    spidx = 0;
    setText();
}

void MainWindow::HoliLoop(){
    for(i=0;i<COM_COUNT;i++){
        digitalWrite(COM[i], HIGH);
        for(j=0;j<PIN_COUNT;j++){
            if(digitalRead(PIN[j])){
                if(COM[i] == COM17){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "->1";
                        state = pagedef.getPage();
                        switch(state){
                        case IDX_Page1:
                            state = START_Page1;
                            break;
                        case MDL_Page1:
                            state = MDL_Page2;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "->2";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "->3";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "->4";
                        state = pagedef.getPage();
                        switch(state){
                        case MDL_Page2:
                            state = MDL_Error;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "COM";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "1";
                        setTextsp("1");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "4";
                        setTextsp("4");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "7";
                        setTextsp("7");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << ".";
                        setTextsp(".");
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM16){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "NAV";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "2";
                        setTextsp("2");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "5";
                        setTextsp("5");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "8";
                        setTextsp("8");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "0";
                        setTextsp("0");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "-";
                        setTextbs();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "Left";
                        if(spidx - 1 >= 0){
                            spidx--;
                        }
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "CLR";
                        clearText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << "Down";
                        state = pagedef.getPage();
                        switch(state){
                        case IDX_Page1:
                            state = IDX_Page2;
                            break;
                        case START_Page1:
                            state = START_Page2;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM15){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "IFF";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "3";
                        setTextsp("3");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "6";
                        setTextsp("6");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "9";
                        setTextsp("9");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "Up";
                        state = pagedef.getPage();
                        switch(state){
                        case IDX_Page2:
                            state = IDX_Page1;
                            break;
                        case START_Page2:
                            state = START_Page1;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "Right";
                        if(spidx + 1 <= pagedata.ScratchPAD.length()){
                            spidx++;
                        }
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "/";
                        setTextsp("/");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "MSN";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << "DATA";
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM14){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "M3";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "A";
                        setTextsp("A");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "B";
                        setTextsp("B");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "G";
                        setTextsp("G");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "H";
                        setTextsp("H");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "M";
                        setTextsp("M");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "N";
                        setTextsp("N");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "S";
                        setTextsp("S");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << "T";
                        setTextsp("T");
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM04){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "STR";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "C";
                        setTextsp("C");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "I";
                        setTextsp("I");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "O";
                        setTextsp("O");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "U";
                        setTextsp("U");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "EDIT";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "IDX";
                        state = IDX_Page1;
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "INAV";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << "STAT";
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM03){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "FPLN";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "D";
                        setTextsp("D");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "J";
                        setTextsp("J");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "P";
                        setTextsp("P");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "V";
                        setTextsp("V");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "Y";
                        setTextsp("Y");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "MARK";
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM02){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "PSN";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "E";
                        setTextsp("E");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "K";
                        setTextsp("K");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "Q";
                        setTextsp("Q");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "W";
                        setTextsp("W");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "Z";
                        setTextsp("Z");
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
                if(COM[i] == COM01){
                    switch(PIN[j]){
                    case PIN05:
                        qDebug() << "1<-";
                        state = pagedef.getPage();
                        switch(state){
                        case MDL_Page2:
                            state = MDL_Page1;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN06:
                        qDebug() << "2<-";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN07:
                        qDebug() << "3<-";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN24:
                        qDebug() << "4<-";
                        state = pagedef.getPage();
                        switch(state){
                        case START_Page1:
                            state = MDL_Page1;
                            break;
                        case MDL_Error:
                            state = MDL_Page1;
                            break;
                        default:
                            break;
                        }
                        pagedata = pagedef.gotoPage(state);
                        setText();
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN25:
                        qDebug() << "DIR";
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN26:
                        qDebug() << "F";
                        setTextsp("F");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN27:
                        qDebug() << "L";
                        setTextsp("L");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN28:
                        qDebug() << "R";
                        setTextsp("R");
                        while(digitalRead(PIN[j]));
                        break;
                    case PIN29:
                        qDebug() << "X";
                        setTextsp("X");
                        while(digitalRead(PIN[j]));
                        break;
                    }
                }
            }
        }
        delay(20);
        digitalWrite(COM[i], LOW);
    }
}
