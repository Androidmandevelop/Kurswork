#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "dialog.hpp"
#include <QActionGroup>
#include <QFileDialog>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QSettings>
#include <QDragEnterEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , Table(new TableModel(this))
  , proxyModel(new ProxyModel(this))
  , contextMenu(new QMenu(this))
{
  ui->setupUi(this);
  readSettings();

  setAcceptDrops(true);

  ui->tableView->setModel(proxyModel);

  ui->tableView->sortByColumn(0, Qt::AscendingOrder);

  contextMenu->addAction(ui->actionAdd);
  contextMenu->addAction(ui->actionDelete);

  connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenu(QPoint)));
  connect(ui->actionAbout_programm, &QAction::triggered, this, &MainWindow::aboutAuthor);
  connect(Table, &TableModel::wasModified, this, &MainWindow::setModified);
  connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

  qApp->installTranslator(&appTranslator);
  qmPath = qApp->applicationDirPath() + "/translations";

  createLanguageMenu();
  // Создание уникального номера
  static int numberFile = 0;
  // Задание имени текущего файла
  OpenedFile = QString("untitled_%1.txt").arg(numberFile++);
  // адание названия главному окну
  setWindowTitle(tr("%1[*] - %2")
                 .arg(OpenedFile, tr("Plotter")));
}


MainWindow::~MainWindow()
{
  writeSettings();

  delete contextMenu;
  delete proxyModel;
  delete Table;
  delete languageActionGroup;
  delete ui;
}

void MainWindow::readSettings()
{
  QSettings settings("MyApplication", "CourseWork");
  restoreGeometry(settings.value("geometryMainWindow").toByteArray());
}

void MainWindow::writeSettings()
{
  QSettings settings("MyApplication", "CourseWork");
  settings.setValue("geometryMainWindow", saveGeometry());
}

void MainWindow::aboutAuthor()
{
  Dialog about(this);
  about.setWindowFlag(Qt::Window);
  about.setWindowTitle(tr("About programm"));
  about.setFixedSize(about.size());
  about.exec();
}

void MainWindow::setModified()
{
  if (!isWindowModified())
    setWindowModified(true);
}

void MainWindow::setCurrentFile(const QString &FileName)
{
    OpenedFile = FileName;
    setWindowModified(false);
    isUntitled = false;

    QString showName;

    if (OpenedFile.isEmpty()) {
        showName = "untitled.txt";
        OpenedFile = showName;
    }
    else
        showName = QFileInfo(OpenedFile).fileName();

    setWindowTitle(tr("%1[*] - %2")
                   .arg(showName, tr("Plotter")));
}

void MainWindow::customMenu(QPoint pos)
{
  contextMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::switchLanguage(QAction *action)
{
  QString locale = action->data().toString();

  appTranslator.load(locale, qmPath);

  ui->retranslateUi(this);
}

void MainWindow::on_actionNew_triggered()
{
  MainWindow *mainWindow = new MainWindow;
  mainWindow->move(pos() + QPoint(30, 30));
  mainWindow->show();
}

void MainWindow::createLanguageMenu()
{
  languageActionGroup = new QActionGroup(this);

  connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);

  QDir dir(qmPath);

  QStringList fileNames = dir.entryList(QStringList("CourseWork_*.qm"));

  for (int i = 0; i < fileNames.count(); i++) {
      QString locale = fileNames[i];

      QTranslator translator;
      translator.load(fileNames[i], qmPath);

      QString language = translator.translate("MainWindow", "English");
      QAction *action = new QAction(QString("&%1 %2")
                                    .arg(i + 1)
                                    .arg(language),
                                    this);
      action->setCheckable(true);
      action->setData(locale);

      ui->menuLanguage->addAction(action);
      languageActionGroup->addAction(action);

      if (language == "English")
        action->setChecked(true);
    }
}

void MainWindow::on_actionOpen_triggered()
{
  if (Table->rowCount(QModelIndex())) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this,
                                    tr("Save and close"),
                                    tr("Do you want to save and close "
                                       "%1 before opening of new file?")
                                    .arg(QFileInfo(OpenedFile).fileName()),
                                    QMessageBox::Yes |
                                    QMessageBox::Cancel);

      if (reply == QMessageBox::Yes) {
          on_actionSave_triggered();
          on_actionClose_triggered();
        }
      else return;
    }

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Document"));

  if (!fileName.isEmpty()) {
      readFile(fileName);
    }

  setCurrentFile(fileName);
}


void MainWindow::readFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           tr("Open Document"),
                           tr("Can not read file %1:\n%2")
                           .arg(QFileInfo(fileName).fileName(),
                                file.errorString()));
      return;
    }

  QTextStream in(&file);

  QStringList StrFormat = {"Default", "A0", "A1", "A2"};
  QStringList StrFormFactor = {"Default", "Jet", "Uneversal"};

  while (!in.atEnd()) {
      QStringList dataList = in.readLine().split(";");

      std::string Manufacturer = dataList[0].toStdString();
      std::string Model = dataList[1].toStdString();
      Proiz Proiz(Manufacturer, Model);

      auto FormFactor = static_cast<Plotter::EnumFormFactor>(StrFormFactor.indexOf(dataList[2]));

      auto Format = static_cast<Plotter::EnumFormat>(StrFormat.indexOf(dataList[3]));

      short SPEED_PRINT = dataList[4].toInt();
      short Max_widht_print = dataList[5].toInt();
      Plotter::Properties Timings = {SPEED_PRINT, Max_widht_print};
      int Price = dataList[6].toInt();

      Plotter ram(Proiz,
               FormFactor,
               Format,
               Timings,
               Price);

      Table->insertValue(ram);
    }

  file.close();

  proxyModel->setSourceModel(Table);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->horizontalHeader()->setStretchLastSection(true);

  ui->actionSave->setEnabled(true);
  ui->actionSave_as->setEnabled(true);
  ui->actionClose->setEnabled(true);
  ui->lineEdit->setEnabled(true);
}

void MainWindow::on_actionSave_triggered()
{
  if (ui->tableView->model()->rowCount() <= 0)
    return;

  writeFile(OpenedFile);
}

void MainWindow::on_actionSave_as_triggered()
{
  if (ui->tableView->model()->rowCount() <= 0)
    return;

  QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Document"),
                                                      QDir::currentPath(),
                                                      "Text Files (*.txt);;All Files (*.*)");
  if (!saveFileName.isEmpty()) {
      writeFile(saveFileName);
    }
}

void MainWindow::writeFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           tr("Save Document"),
                           tr("Can not write file %1:\n%2")
                           .arg(QFileInfo(fileName).fileName(), file.errorString()));
      return;
    }

  QTextStream out(&file);

  QList<Plotter> list = Table->getQList();

  const char *StrFormFactor[] = {"Default", "Jet", "Uneversal"};
  const char *StrFormat[] = {"Default", "A0", "A1", "A2"};

  for (auto it = list.begin(); it != list.end(); ++it)
    {
      out << it->getManufacturer().c_str() << ';'
          << it->getModel().c_str() << ';'
          << StrFormFactor[it->getFormFactor()] << ';'
          << StrFormat[it->getFormat()] << ';'
          << it->getProperties().SPEED_PRINT << ';'
          << it->getProperties().Max_widht_print << ';'
          << it->getPrice() << ";\n";
    }

  file.close();
}

void MainWindow::on_actionClose_triggered()
{
  proxyModel->setSourceModel(nullptr);

  Table->clear();
  setCurrentFile(QString());

  ui->actionSave->setEnabled(false);
  ui->actionSave_as->setEnabled(false);
  ui->actionClose->setEnabled(false);
  ui->lineEdit->setEnabled(false);
}

void MainWindow::on_actionAdd_triggered()
{
  if (OpenedFile.isEmpty()) {
      QMessageBox::warning(this,
                           tr("Error of appending"),
                           tr("Can not append entry. Probably, table is empty..."));
      return;
    }

  Table->insertRows(0, 1, QModelIndex());

  for (int row = 0; row < Table->rowCount(QModelIndex()); row++) {
      QModelIndex indexItem = proxyModel->index(row, 3);
      if (indexItem.data().toString() == "Default") {
          ui->tableView->selectRow(indexItem.row());
          break;
        }
    }
}

void MainWindow::on_actionDelete_triggered()
{
  if (!Table->rowCount(QModelIndex())) {
      QMessageBox::warning(this,
                           tr("Error of deleting"),
                           tr("Can not deleting entry. Probably, table is empty..."));
      return;
    }

  int row = proxyModel->mapToSource(ui->tableView->currentIndex()).row();
  Table->removeRows(row, 1, QModelIndex());
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
  QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(QRegExp::FixedString);
  QRegExp regExp(text, Qt::CaseInsensitive, syntax);

  int columnIndex = ui->comboBox->currentIndex() - 1;

  proxyModel->setFilterKeyColumn(columnIndex);
  proxyModel->setFilterRegExp(regExp);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
  foreach (auto url, event->mimeData()->urls())
    {
      QFileInfo fileName(url.toLocalFile());

      if (fileName.fileName() != "")
        {
          if (!fileName.isDir())
            {
              if (fileName.completeSuffix() == "txt")
                {
                  event->accept();
                  return;
                }
            }
        }
      event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
  foreach (auto url, event->mimeData()->urls())
    {
      if (Table->rowCount(QModelIndex())) {
          if (QMessageBox::Yes == QMessageBox::question(this,
                                                        tr("Save and close"),
                                                        tr("Do you want to save and close "
                                                           "%1 before opening of "
                                                           "new file?").arg(QFileInfo(OpenedFile).fileName()),
                                                        QMessageBox::Yes |
                                                        QMessageBox::Cancel)) {
              on_actionSave_triggered();
              on_actionClose_triggered();
            } else {
              return;
            }
        }

      QString fileName = url.toLocalFile();

      readFile(fileName);
      setCurrentFile(fileName);
    }
}



void MainWindow::on_actionSpeed_of_Print_triggered()
{
  Chart *chart = createChart();

  if (chart == nullptr)
    return;

  chart->SpeedPrint();
}

void MainWindow::on_actionPrice_triggered()
{
  Chart *chart = createChart();

  if (chart == nullptr)
    return;

  chart->Price();
}

Chart *MainWindow::createChart()
{
  if (Table->rowCount(QModelIndex()) < 2)
  {
      QMessageBox::warning(this, tr("Result"), tr("Few records"));
      return nullptr;
  }

  Chart *graphicWindow = new Chart(Table->getQList());
  graphicWindow->setWindowFlag(Qt::Window);
  graphicWindow->setWindowTitle(QFileInfo(OpenedFile).fileName() + tr(" - Charts"));
  graphicWindow->setAttribute(Qt::WA_DeleteOnClose);
  graphicWindow->show();

  return graphicWindow;
}
