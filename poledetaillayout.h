#include <QBoxLayout>
#include "qlineedit.h"
#include "qlabel.h"
#include "gecccospolewidth.h"

class PoleDetailLayout : public QWidget
{
public:
    PoleDetailLayout();
    void showPole(GecccosPoleWidth* width);
    void showEmptyPole();
    void changeValues();
private:
    QGridLayout* mainLayout;
    GecccosPoleWidth* width;

    //value
    QHBoxLayout* valueLayout;
    QLineEdit* valueEdit;
    //variation
    QHBoxLayout* variationLayout;
    QLineEdit* variationEdit;
    //jTot
    QHBoxLayout* jTotalLayout;
    QLabel* jTotalLabel;

    //partition
    QHBoxLayout* partitionLayout;
    QLabel* partitionLabel;

    //target
    QHBoxLayout* targetLayout;
    QLabel* targetLabel;

    //projectile
    QHBoxLayout* projectileLayout;
    QLabel* projectileLabel;

    //SpinTot
    QHBoxLayout* totalSpinLayout;
    QLabel* totalSpinLabel;

    //target
    QHBoxLayout* targetSpinLayout;
    QLabel* targetSpinLabel;

    //projectile
    QHBoxLayout* projectileSpinLayout;
    QLabel* projectileSpinLabel;

    //aprojectile
    QHBoxLayout* aProjectileLayout;
    QLabel* aProjectileLabel;

    //aTarget
    QHBoxLayout* aTargetLayout;
    QLabel* aTargetLabel;

    //qval
    QHBoxLayout* qValueLayout;
    QLabel* qValueLabel;

    //1
    QHBoxLayout* oneLayout;
    QLabel* oneLabel;

    //hbc2mc2
    QHBoxLayout* hbc2mc2Layout;
    QLabel* hbc2mc2Label;

    //energyDelta
    QHBoxLayout* energyDeltaLayout;
    QLabel* energyDeltaLabel;
};
