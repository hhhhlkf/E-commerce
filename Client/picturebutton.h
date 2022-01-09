#ifndef PICTUREBUTTON_H
#define PICTUREBUTTON_H

#include <QObject>
#include <QAbstractButton>
//轮播图按钮
class pictureButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit pictureButton(QWidget *parent = nullptr);
    ~pictureButton();
    int id()const;
    void setId(int id);

signals:
    void entered();
    void entered(int);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
public slots:

private:
    bool m_isSelected;
    int m_id;
};

#endif // PICTUREBUTTON_H
