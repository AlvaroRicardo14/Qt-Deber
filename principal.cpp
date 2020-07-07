#include "principal.h"
#include "ui_principal.h"
#include <QFileDialog>


Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    connect(ui->cmdCalcular, SIGNAL(released()),
            this, SLOT(calcular()));
    connect(ui->mnuCalcular, SIGNAL(triggered(bool)),
            this, SLOT(calcular()));
    connect(ui->mnuSalir, SIGNAL(triggered(bool)),
            this, SLOT(close()));
    connect(ui->mnuGuardar, SIGNAL(triggered(bool)),
            this, SLOT(guardar()));




}

Principal::~Principal()
{
    delete ui;
}

void Principal::calcular()
{

    //Obtener Datos
    QString nombre = ui->intNombre->text();
    int horas = ui->intHoras->value();

    if ( nombre == "" || horas == 0){
        ui->statusbar->showMessage("No se han ingresado datos a calcular",5000);
        return;
    }else{
        ui->statusbar->clearMessage();
    }

    float const HORA_EXTRA = 20.10;

    //Calcula horas extras.

    int extra = 0;
    if(horas > 40){
        extra = horas - 40;
        horas = 40;
    }

    //Calculo del salario

    float salario = 0;

    if(ui->intMatutina->isChecked()){
        salario = horas * 5.15 + extra * HORA_EXTRA;
    }else if(ui->intVespertina->isChecked()){
        salario = horas * 8.50 + extra * HORA_EXTRA;
    }else{
        salario = horas *12.65 + extra * HORA_EXTRA;

    }
    //Calcular el descuento.

    float descuento = salario * 9.5 /100;
    float salario_neto = salario - descuento;


    //Imprimir Resultados

    QString resultado = "\n Obrero: " + nombre + "\n";
    resultado += "Salario: " + QString::number(salario) + "\n";
    resultado += "Descuento (9.50): " + QString::number(descuento) + "\n";
    resultado += "Salario: " + QString::number(salario_neto) + "\n";
    resultado += "---\n---";

   ui->outResultado->appendPlainText(resultado);
   limpiar();

}

void Principal::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            "Guardar Datos", "c:/users/ricar/Documentos", "Archivo de texto(*.txt)");

    QFile data (fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream salida(&data);
        salida<< ui->outResultado->toPlainText();
        ui->statusbar->showMessage("Datos Guardados en " + fileName,5000);
    }
    data.close();
}

void Principal::limpiar()
{
    ui->intNombre->setText(" ");
    ui->intHoras->setValue(0);
    ui->intMatutina->setChecked(true);
    ui->intNombre->setFocus();
}

