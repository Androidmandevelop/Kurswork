#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "proxymodel.hpp"
#include "tablemodel.hpp"
#include "chart.hpp"

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  /**
   * @brief createLanguageMenu Создание меню языка
   */
  void createLanguageMenu();
  /**
   * @brief readFile Чтение файла
   * @param fileName Имя файла
   */
  void readFile(const QString& fileName);
  /**
   * @brief writeFile Запись данных в файл
   * @param fileName Имя файла
   */
  void writeFile(const QString& fileName);
  /**
   * @brief readSettings Чтение запоминающих настроек
   */
  void readSettings();
  /**
   * @brief writeSettings Запись запоминающих настроек
   */
  void writeSettings();

  void setModified();

  void setCurrentFile(const QString &FileName);

  Chart* createChart();

private slots:
  /**
   * @brief Об авторе
   */
  void aboutAuthor();
  /**
   * @brief customMenu Контекстное меню
   * @param pos Его позиция
   */
  void customMenu(QPoint pos);
  /**
   * @brief switchLanguage Смена языка
   * @param action Выбранный язык
   */
  void switchLanguage(QAction *action);


  void on_actionSpeed_of_Print_triggered();

  void on_actionPrice_triggered();

  void on_actionNew_triggered();
  /**
   * @brief on_actionOpen_triggered Триггер открытия файла
   */
  void on_actionOpen_triggered();
  /**
   * @brief on_actionSave_triggered Триггер сохранения текущего файла
   */
  void on_actionSave_triggered();
  /**
   * @brief on_actionSave_as_triggered Триггер сохранения файла как ...
   */
  void on_actionSave_as_triggered();
  /**
   * @brief on_actionClose_triggered Триггер закрытия файла
   */
  void on_actionClose_triggered();
  /**
   * @brief on_actionAdd_triggered Триггер добавления записи
   */
  void on_actionAdd_triggered();
  /**
   * @brief on_actionDelete_triggered Триггер удаления записи
   */
  void on_actionDelete_triggered();
  /**
   * @brief on_lineEdit_textChanged Триггер измения содержимого
   * @param text Введенный текст
   */
  void on_lineEdit_textChanged(const QString& text);

private:
  Ui::MainWindow *ui;
  /**
   * @brief Модель, хранящая данные
   */
  TableModel *Table;
  /**
   * @brief proxyModel Модель для сортировки и поиска
   */
  ProxyModel *proxyModel;
  /**
   * @brief contextMenu Контекстное меню
   */
  QMenu *contextMenu;
  /**
   * @brief languageActionGroup Группа с выбором языка
   */
  QActionGroup *languageActionGroup;
  /**
   * @brief appTranslator Переводчик приложения
   */
  QTranslator appTranslator;
  /**
   * @brief qmPath Местоположение переводов
   */
  QString qmPath;
  /**
   * @brief OpenedFile Текущий открытый файл
   */
  QString OpenedFile;

  bool isUntitled;

protected:
  /**
   * @brief Событие наведения файла на программу
   * @param event Объект класса события QDragEnterEvent
   */
  void dragEnterEvent(QDragEnterEvent* event) override;
  /**
   * @brief Событие на отпускание файла в программу
   * @param event Объект класса события QDropEvent
   */
  void dropEvent(QDropEvent* event) override;

};
#endif // MAINWINDOW_HPP
