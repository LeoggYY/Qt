#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>

class Example : public QWidget {
public:
    Example(QWidget *parent = nullptr) : QWidget(parent) {

        QVBoxLayout *layout = new QVBoxLayout(this);

        QTabWidget *tabWidget = new QTabWidget(this);

        QWidget *tab1 = new QWidget();
        QWidget *tab2 = new QWidget();
        QWidget *tab3 = new QWidget();
        QWidget *tab4 = new QWidget();
        // 內容
        QLabel *label1 = new QLabel("隊長:41243147楊承哲\n組員1:41243219林厚丞\n組員2:41243239陳裕祥\n組員3:41243244黃順駿", tab1);

        QVBoxLayout *tab1Layout = new QVBoxLayout();
        tab1Layout->addWidget(label1);
        tab1->setLayout(tab1Layout);


        tabWidget->addTab(tab1, "隊長");
        tabWidget->addTab(tab2, "組員1");
        tabWidget->addTab(tab3, "組員2");
        tabWidget->addTab(tab4, "組員3");


        layout->addWidget(tabWidget);

        setLayout(layout);
        setWindowTitle("分組作業");
        resize(300, 200);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Example window;
    window.show();

    return app.exec();
}
