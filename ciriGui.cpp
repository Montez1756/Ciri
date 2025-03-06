#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainter>

class GlowingButton : public QPushButton {
    Q_OBJECT

public:
    GlowingButton(QWidget* parent = nullptr) : QPushButton(parent) {
        // Set initial style for the button with a subtle border
        setStyleSheet("QPushButton {"
                      "border: 2px solid transparent;"
                      "border-radius: 5px;"
                      "background-color: #2E2E2E;"
                      "color: white;"
                      "padding: 10px 20px;"
                      "font-size: 18px;"
                      "}");

        // Create the glow animation
        glowAnimation = new QPropertyAnimation(this, "borderColor", this);
        glowAnimation->setDuration(1000);  // 1 second animation duration
        glowAnimation->setLoopCount(-1);  // Infinite loop

        glowAnimation->setStartValue(QColor(0, 255, 255));  // Starting glow color (cyan)
        glowAnimation->setEndValue(QColor(255, 0, 255));    // Ending glow color (magenta)
        glowAnimation->setEasingCurve(QEasingCurve::InOutQuad);  // Smooth easing effect
        glowAnimation->start();
    }

private:
    QPropertyAnimation* glowAnimation;

protected:
    // Override paintEvent to dynamically update the border color
    void paintEvent(QPaintEvent* event) override {
        QPushButton::paintEvent(event);  // Call the base class to paint the button
        QPainter painter(this);
        QPen pen(glowAnimation->currentValue().value<QColor>());
        painter.setPen(pen);
        painter.drawRect(rect().adjusted(1, 1, -1, -1));  // Draw border
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    GlowingButton* button = new GlowingButton(&window);
    button->setText("Click Me");
    button->resize(200, 50);
    button->move(100, 100);

    window.setWindowTitle("Siri-like Border Effect");
    window.resize(400, 300);
    window.show();

    return app.exec();
}
