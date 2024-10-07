#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

class Example : public QWidget {
public:
    Example(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QTabWidget *tabWidget = new QTabWidget(this);

        QWidget *tab1 = new QWidget();
        QWidget *tab2 = new QWidget();
        QWidget *tab3 = new QWidget();
        QWidget *tab4 = new QWidget();

        label1 = new QLabel("隊長:41243147楊承哲\n組員1:41243219林厚丞\n組員2:41243239陳裕翔\n組員3:41243244黃順駿", tab1);

        QVBoxLayout *tab1Layout = new QVBoxLayout();
        tab1Layout->addWidget(label1);
        tab1->setLayout(tab1Layout);

        tabWidget->addTab(tab1, "隊長");
        tabWidget->addTab(tab2, "組員1");
        tabWidget->addTab(tab3, "組員2");
        tabWidget->addTab(tab4, "組員3");

        layout->addWidget(tabWidget);

        QPushButton *colorButton = new QPushButton("更改字體顏色", tab2);
        connect(colorButton, &QPushButton::clicked, this, &Example::changeFontColor);

        QVBoxLayout *tab2Layout = new QVBoxLayout();
        tab2Layout->addWidget(colorButton);
        tab2->setLayout(tab2Layout);

        QPushButton *changeFontButton = new QPushButton("更改文字樣式", tab3);
        connect(changeFontButton, &QPushButton::clicked, this, &Example::changeFontStyle);

        QVBoxLayout *tab3Layout = new QVBoxLayout();
        tab3Layout->addWidget(changeFontButton);
        tab3->setLayout(tab3Layout);

        addChangeFilePathButton(tab2, 1);
        addChangeFilePathButton(tab3, 2);
        addChangeFilePathButton(tab4, 3);

        setLayout(layout);
        setWindowTitle("分組作業");
        resize(300, 200);
    }

private slots:
    void changeFontColor() {
        QTabWidget *tabWidget = findChild<QTabWidget *>();
        if (!tabWidget) return;

        QWidget *tab1 = tabWidget->widget(0);
        if (!tab1) return;

        QLabel *label = tab1->findChild<QLabel *>();
        if (!label) return;

        QColor color = QColorDialog::getColor(label->palette().color(QPalette::Text), this, "選擇字體顏色");
        if (color.isValid()) {
            QPalette palette = label->palette();
            palette.setColor(QPalette::WindowText, color);
            label->setPalette(palette);
            label->setAutoFillBackground(true);
        }
    }

    void changeFontStyle() {
        if (label1) {
            bool ok;
            QFont font = QFontDialog::getFont(&ok, label1->font(), this, "選擇字體樣式");
            if (ok) {
                label1->setFont(font);
            }
        }
    }

    void changeFilePath(int tabIndex) {
        QString filePath = QFileDialog::getOpenFileName(this, "選擇文件");
        if (!filePath.isEmpty()) {
            QTabWidget *tabWidget = findChild<QTabWidget *>();
            if (!tabWidget) return;

            QWidget *tab = tabWidget->widget(tabIndex);
            if (!tab) return;

            QLabel *label = tab->findChild<QLabel *>();
            if (!label) {
                label = new QLabel(tab);
                QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(tab->layout());
                if (layout) {
                    layout->addWidget(label);
                }
            }
            label->setText(filePath);
        }
    }

private:
    QLabel *label1;

    void addChangeFilePathButton(QWidget *tab, int tabIndex) {
        QPushButton *button = new QPushButton("選擇文件", tab);
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(tab->layout());
        if (layout) {
            layout->addWidget(button);
        } else {
            QVBoxLayout *newLayout = new QVBoxLayout();
            newLayout->addWidget(button);
            tab->setLayout(newLayout);
        }
        connect(button, &QPushButton::clicked, [this, tabIndex]() { changeFilePath(tabIndex); });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Example window;
    window.show();

    return app.exec();
}

