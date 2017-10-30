#include "mainwindow.h"
#include <dtitlebar.h>

MainWindow::MainWindow(DMainWindow *parent)
    : DMainWindow(parent)                                         
{
    mainWidget = new QWidget;
    mainLayout = new QGridLayout(mainWidget);
    titleBar = new TitleBar;
    displayArea = new DisplayArea;
    clearButton= new TextButton("C");
    backButton= new TextButton("←");
    modButton= new TextButton("%");
    divButton= new TextButton("÷");
    num7Button= new TextButton("7");
    num8Button= new TextButton("8");
    num9Button= new TextButton("9");
    multButton= new TextButton("×");
    num4Button= new TextButton("4");
    num5Button= new TextButton("5");
    num6Button= new TextButton("6");
    minButton= new TextButton("－");
    num1Button= new TextButton("1");
    num2Button= new TextButton("2");
    num3Button= new TextButton("3");
    plusButton= new TextButton("＋");
    zeroButton= new TextButton("0");
    pointButton= new TextButton(".");
    bracketsButton= new TextButton("( )");
    equalButton= new TextButton("＝");

    divButton->setObjectName("SymbolButton");
    multButton->setObjectName("SymbolButton");
    minButton->setObjectName("SymbolButton");
    plusButton->setObjectName("SymbolButton");
    equalButton->setObjectName("EqualButton");

    mainLayout->addWidget(displayArea, 0, 0, 1, 4);
    mainLayout->addWidget(clearButton, 1, 0);
    mainLayout->addWidget(backButton, 1, 1);
    mainLayout->addWidget(modButton, 1, 2);
    mainLayout->addWidget(divButton, 1, 3);
    mainLayout->addWidget(num7Button, 2, 0);
    mainLayout->addWidget(num8Button, 2, 1);
    mainLayout->addWidget(num9Button, 2, 2);
    mainLayout->addWidget(multButton, 2, 3);
    mainLayout->addWidget(num4Button, 3, 0);
    mainLayout->addWidget(num5Button, 3, 1);
    mainLayout->addWidget(num6Button, 3, 2);
    mainLayout->addWidget(minButton, 3, 3);
    mainLayout->addWidget(num1Button, 4, 0);
    mainLayout->addWidget(num2Button, 4, 1);
    mainLayout->addWidget(num3Button, 4, 2);
    mainLayout->addWidget(plusButton, 4, 3);
    mainLayout->addWidget(zeroButton, 5, 0);
    mainLayout->addWidget(pointButton, 5, 1);
    mainLayout->addWidget(bracketsButton, 5, 2);
    mainLayout->addWidget(equalButton, 5, 3);

    titlebar()->setCustomWidget(titleBar, Qt::AlignVCenter, false);
    titlebar()->setWindowFlags(titlebar()->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    titlebar()->setSeparatorVisible(true);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setFixedSize(330, 490);
    setCentralWidget(mainWidget);
    
    connect(zeroButton, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("0");
    });
    connect(num1Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("1");
    });
    connect(num2Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("2");
    });
    connect(num3Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("3");
    });
    connect(num4Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("4");
    });
    connect(num5Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("5");
    });
    connect(num6Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("6");
    });
    connect(num7Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("7");
    });
    connect(num8Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("8");
    });
    connect(num9Button, &QPushButton::clicked, this, [=]{
        onNumberButtonClicked("9");
    });
    connect(plusButton, &QPushButton::clicked, this, [=]{
        onSymbolButtonClicked("+");
    });
    connect(minButton, &QPushButton::clicked, this, [=]{
        onSymbolButtonClicked("-"); 
    });
    connect(multButton, &QPushButton::clicked, this, [=]{
        onSymbolButtonClicked("×");
    });
    connect(divButton, &QPushButton::clicked, this, [=]{
        onSymbolButtonClicked("÷"); 
    });
    connect(equalButton, &QPushButton::clicked, this, &MainWindow::onEqualButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::onBackButtonClicked);
    connect(pointButton, &QPushButton::clicked, this, &MainWindow::onPointButtonClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onNumberButtonClicked(const QString &str)
{
    displayArea->insertStrToItem(str);
    displayArea->scrollToBottom();
}

void MainWindow::onBackButtonClicked()
{
    displayArea->backspace();
}

void MainWindow::onPointButtonClicked()
{
    displayArea->insertStrToItem(".");
    displayArea->scrollToBottom();
}

void MainWindow::onSymbolButtonClicked(const QString &str)
{
    displayArea->insertStrToItem(str);
    displayArea->scrollToBottom();
}

void MainWindow::onClearButtonClicked()
{
    displayArea->clearLastItem();
    displayArea->addNextLine("0");
}

void MainWindow::onEqualButtonClicked()
{
    displayArea->addNextLine("0");
    displayArea->scrollToBottom();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_0) {
        onNumberButtonClicked("0");
    }else if (e->key() == Qt::Key_1) {
        onNumberButtonClicked("1");
    }else if (e->key() == Qt::Key_2) {
        onNumberButtonClicked("2");
    }else if (e->key() == Qt::Key_3) {
        onNumberButtonClicked("3");
    }else if (e->key() == Qt::Key_4) {
        onNumberButtonClicked("4");
    }else if (e->key() == Qt::Key_5) {
        onNumberButtonClicked("5");
    }else if (e->key() == Qt::Key_6) {
        onNumberButtonClicked("6");
    }else if (e->key() == Qt::Key_7) {
        onNumberButtonClicked("7");
    }else if (e->key() == Qt::Key_8) {
        onNumberButtonClicked("8");
    }else if (e->key() == Qt::Key_9) {
        onNumberButtonClicked("9");
    }else if (e->key() == Qt::Key_Plus) {
        onSymbolButtonClicked("+");
    }else if (e->key() == Qt::Key_Minus) {
        onSymbolButtonClicked("-");
    }else if (e->key() == Qt::Key_Asterisk) {
        onSymbolButtonClicked("×");
    }else if (e->key() == Qt::Key_Slash) {
        onSymbolButtonClicked("÷");
    }else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        onEqualButtonClicked();
    }else if (e->key() == Qt::Key_Backspace) {
        displayArea->backspace();
    }
}