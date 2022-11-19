#include "poledetaillayout.h"

PoleDetailLayout::PoleDetailLayout()
{
    this->width=nullptr;
    mainLayout=new QGridLayout();
    //value
    valueLayout=new QHBoxLayout();
    valueLayout->addWidget(new QLabel("value: "));
    valueEdit = new QLineEdit("");
    valueLayout->addWidget(valueEdit);

    //variation
    variationLayout=new QHBoxLayout();
    variationLayout->addWidget(new QLabel("variation +/- : "));
    variationEdit=new QLineEdit("");
    variationLayout->addWidget(variationEdit);

    //jTot
    jTotalLayout=new QHBoxLayout();
    jTotalLayout->addWidget(new QLabel("J total: "));
    jTotalLabel = new QLabel("");
    jTotalLayout->addWidget(jTotalLabel);

    mainLayout->addLayout(valueLayout,0,0);
    mainLayout->addLayout(variationLayout,0,1);
    mainLayout->addLayout(jTotalLayout,0,2);

    //partition
    partitionLayout=new QHBoxLayout();
    partitionLayout->addWidget(new QLabel("Partition: "));
    partitionLabel = new QLabel("");
    partitionLayout->addWidget(partitionLabel);

    //target
    targetLayout=new QHBoxLayout();
    targetLayout->addWidget(new QLabel("target: "));
    targetLabel = new QLabel("");
    targetLayout->addWidget(targetLabel);

    //projectile
    projectileLayout=new QHBoxLayout();
    projectileLayout->addWidget(new QLabel("projectile"));
    projectileLabel = new QLabel("");
    projectileLayout->addWidget(projectileLabel);

    mainLayout->addLayout(partitionLayout,2,0);
    mainLayout->addLayout(targetLayout,2,1);
    mainLayout->addLayout(projectileLayout,2,2);

    //SpinTot
    totalSpinLayout=new QHBoxLayout();
    totalSpinLayout->addWidget(new QLabel("Total Spin: "));
    totalSpinLabel = new QLabel("");
    totalSpinLayout->addWidget(totalSpinLabel);

    //target
    targetSpinLayout=new QHBoxLayout();
    targetSpinLayout->addWidget(new QLabel("Target Spin: "));
    targetSpinLabel = new QLabel("");
    targetSpinLayout->addWidget(targetSpinLabel);

    //projectile
    projectileSpinLayout=new QHBoxLayout();
    projectileSpinLayout->addWidget(new QLabel("Projectile Spin: "));
    projectileSpinLabel = new QLabel("");
    projectileSpinLayout->addWidget(projectileSpinLabel);

    mainLayout->addLayout(totalSpinLayout,3,0);
    mainLayout->addLayout(targetSpinLayout,3,1);
    mainLayout->addLayout(projectileSpinLayout,3,2);

    //aprojectile
    aProjectileLayout=new QHBoxLayout();
    aProjectileLayout->addWidget(new QLabel("A Projectile: "));
    aProjectileLabel = new QLabel("");
    aProjectileLayout->addWidget(aProjectileLabel);

    //aTarget
    aTargetLayout=new QHBoxLayout();
    aTargetLayout->addWidget(new QLabel("A Target: "));
    aTargetLabel = new QLabel("");
    aTargetLayout->addWidget(aTargetLabel);

    //qval
    qValueLayout=new QHBoxLayout();
    qValueLayout->addWidget(new QLabel("Q Value: "));
    qValueLabel = new QLabel("");
    qValueLayout->addWidget(qValueLabel);

    mainLayout->addLayout(aProjectileLayout,4,0);
    mainLayout->addLayout(aTargetLayout,4,1);
    mainLayout->addLayout(qValueLayout,4,2);

    //1
    oneLayout=new QHBoxLayout();
    oneLayout->addWidget(new QLabel("1: "));
    oneLabel = new QLabel("");
    oneLayout->addWidget(oneLabel);

    //hbc2mc2
    hbc2mc2Layout=new QHBoxLayout();
    hbc2mc2Layout->addWidget(new QLabel("hbc2mc2: "));
    hbc2mc2Label = new QLabel("");
    hbc2mc2Layout->addWidget(hbc2mc2Label);

    //energyDelta
    energyDeltaLayout=new QHBoxLayout();
    energyDeltaLayout->addWidget(new QLabel("Energy Delta: "));
    energyDeltaLabel = new QLabel("");
    energyDeltaLayout->addWidget(energyDeltaLabel);

    mainLayout->addLayout(oneLayout,5,0);
    mainLayout->addLayout(hbc2mc2Layout,5,1);
    mainLayout->addLayout(energyDeltaLayout,5,2);
    this->setLayout(mainLayout);
}

void PoleDetailLayout::showPole(GecccosPoleWidth* width, bool variationEnabled){
    this->width=width;
    jTotalLabel->clear();
    //value
    valueEdit->setText(QVariant(width->getValue()).toString());

    //variation
    variationEdit->setText(QVariant(width->getVariation()).toString());
    if (variationEnabled){
        variationEdit->setEnabled(true);
    }else {
        variationEdit->setEnabled(false);
        variationEdit->setToolTip("The variation can only be set when prototype settings are enabeld in the config");

    }


    //jTot
    jTotalLabel->setText(QVariant(width->getJTot()).toString());

    //partition
    partitionLabel->setText(QVariant(width->getPartition()).toString());

    //target
    targetLabel->setText(QVariant(width->getTarget()).toString());

    //projectile
    projectileLabel->setText(QVariant(width->getProjectile()).toString());

    //SpinTot
    totalSpinLabel->setText(QVariant(width->getITot()).toString());

    //targetSpin
    targetSpinLabel->setText(QVariant(width->getITarget()).toString());

    //projectile
    projectileSpinLabel->setText(QVariant(width->getIProjectile()).toString());

    //aprojectile
    aProjectileLabel->setText(QVariant(width->getApr()).toString());

    //aTarget
    aTargetLabel->setText(QVariant(width->getATa()).toString());

    //qval
    qValueLabel->setText(QVariant(width->getQval()).toString());

    //1
    oneLabel->setText(QVariant(width->getOne()).toString());

    //hbc2mc2
    hbc2mc2Label->setText(QVariant(width->getHbc2mc2()).toString());

    //energyDelta
    energyDeltaLabel->setText(QVariant(width->getEnerDelta()).toString());

    this->update();
}

void PoleDetailLayout::showEmptyPole(){

    this->width=nullptr;
    //value
    valueEdit->setText("");

    //variation
    variationEdit->setText("");

    //jTot
    jTotalLabel->setText("");

    //partition
    partitionLabel->setText("");

    //target
    targetLabel->setText("");

    //projectile
    projectileLabel->setText("");

    //SpinTot
    totalSpinLabel->setText("");

    //targetSpin
    targetSpinLabel->setText("");

    //projectile
    projectileSpinLabel->setText("");

    //aprojectile
    aProjectileLabel->setText("");

    //aTarget
    aTargetLabel->setText("");

    //qval
    qValueLabel->setText("");

    //1
    oneLabel->setText("");

    //hbc2mc2
    hbc2mc2Label->setText("");

    //energyDelta
    energyDeltaLabel->setText("");

    this->update();
}

void PoleDetailLayout::changeValues(){

    if (this->width!=nullptr){

        //value
        bool status;
        QString text = this->valueEdit->text();
        double value = text.toDouble(&status);
        if (status){
            this->width->value=value;
        }


        //variation
        text = this->variationEdit->text();
        value = text.toDouble(&status);
        if (status){
            this->width->variation=value;
        }

    }
}




