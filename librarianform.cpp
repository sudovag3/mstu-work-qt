#include "librarianform.h"
#include "ui_librarianform.h"
#include "authwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "book.h"
#include "editbookform.h"
#include<QDebug>
#include "student.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

Librarianform::Librarianform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Librarianform)
{
    ui->setupUi(this);
    update_book_list();
    update_student_list();
}

Librarianform::~Librarianform()
{
    delete ui;
}

void Librarianform::on_ButtonClose_clicked()
{
    AuthWindow *authwind = new AuthWindow(this);
    authwind->show();
    this->hide();
}

void Librarianform::on_bookEdited() {
    QMessageBox::information(this, tr("Успешно"),
                             tr("Книга отредактирована успешно!"));
    update_book_list();
}

void Librarianform::update_book_list(const QString& author, const QString& title) {
    ui->bookListWidget->clear(); // Очищаем список книг

    QList<Book> book_list = Book::books(author, title);
    for (Book &book : book_list) {
        QString book_info = QString("Название: %1, Автор: %2, Описание: %3, Жанр: %4, Количество: %5")
                        .arg(book.title())
                        .arg(book.author())
                        .arg(book.description())
                        .arg(book.genre())
                        .arg(book.quantity());
        QListWidgetItem* item = new QListWidgetItem(ui->bookListWidget);
        item->setSizeHint(QSize(0, 60)); // Задаем фиксированную высоту для строки списка
        item->setTextAlignment(Qt::AlignVCenter); // Выравнивание текста по вертикальному центру

        // Создаем виджет с информацией о книге
        QWidget* bookWidget = new QWidget(ui->bookListWidget);
        QVBoxLayout* bookLayout = new QVBoxLayout(bookWidget);
        QLabel* bookInfoLabel = new QLabel(book_info);
        bookLayout->addWidget(bookInfoLabel);

        // Создаем виджет с кнопками
        QWidget* buttonWidget = new QWidget(ui->bookListWidget);
        QGridLayout* buttonLayout = new QGridLayout(buttonWidget);
        QPushButton* editButton = new QPushButton("Редактировать");
        QPushButton* deleteButton = new QPushButton("Удалить");
        buttonLayout->addWidget(editButton, 0, 0);
        buttonLayout->addWidget(deleteButton, 0, 1);

        // Добавляем виджеты к элементу списка
        bookLayout->addWidget(buttonWidget);
        item->setSizeHint(bookWidget->sizeHint());
        ui->bookListWidget->setItemWidget(item, bookWidget);

        connect(editButton, &QPushButton::clicked, [=]() {
            // Создаем и показываем форму редактирования книги
            EditBookForm *editBookForm = new EditBookForm(&book);
            editBookForm->setAttribute(Qt::WA_DeleteOnClose);
            connect(editBookForm, &EditBookForm::bookEdited, this, &Librarianform::on_bookEdited);
            editBookForm->open();
        });

        connect(deleteButton, &QPushButton::clicked, [=]() {
            // Удаляем книгу из файла
            qInfo() << "Book Id = " << book.id();
            Book::getBookById(book.id()).remove();


            // Удаляем книгу из списка книг
            delete item;

            // Вызываем сигнал, что книга была удалена
            emit bookDeleted();
            update_book_list();
        });
    }
}

void Librarianform::update_student_list() {
    ui->studentListWidget->clear(); // Очищаем список студентов

    QList<Student> student_list = Student::getStudents();
    for (Student &student : student_list) {
        QString student_info = QString("Login: %1")
                        .arg(student.get_login());
        QListWidgetItem* item = new QListWidgetItem(ui->studentListWidget);
        item->setSizeHint(QSize(0, 60)); // Задаем фиксированную высоту для строки списка
        item->setTextAlignment(Qt::AlignVCenter); // Выравнивание текста по вертикальному центру

        // Создаем виджет с информацией о студенте
        QWidget* studentWidget = new QWidget(ui->studentListWidget);
        QVBoxLayout* studentLayout = new QVBoxLayout(studentWidget);
        QLabel* studentInfoLabel = new QLabel(student_info);
        studentLayout->addWidget(studentInfoLabel);

        // Создаем виджет с кнопками
        QWidget* buttonWidget = new QWidget(ui->studentListWidget);
        QGridLayout* buttonLayout = new QGridLayout(buttonWidget);
        QPushButton* detailButton = new QPushButton("Подробнее");
        buttonLayout->addWidget(detailButton, 0, 0);

        // Добавляем виджеты к элементу списка
        studentLayout->addWidget(buttonWidget);
        item->setSizeHint(studentWidget->sizeHint());
        ui->studentListWidget->setItemWidget(item, studentWidget);

        connect(detailButton, &QPushButton::clicked, [=]() {
            // Код, который покажет окно с информацией о студенте
            // Получаем список книг студента из файла studentbooks.json
            QFile file("studentbooks.json");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::warning(this, "Внимание","Произошли проблемы с открытием файла \nСкорее всего, никто из студентов еще не брал книг");
                qWarning() << "Failed to open file";
                return;
            }
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            file.close();
            QJsonObject student_books = doc.object();
            if (!student_books.contains(student.get_login())) {
                QMessageBox::information(this, "Информация","У студента отсутсвуют задолженности");
                qWarning() << "Student does not exist in the book file";
                return;
            }

            QJsonArray books = student_books[student.get_login()].toArray();
            QString book_list = "Books: \n";
            for (const QJsonValue &book : books) {
                QJsonObject bookObj = book.toObject();
                QString bookId = bookObj["Idd_Book"].toString();
                Book book_ = Book::getBookById(bookId);

                    // Добавляем информацию о книге в список
                book_list += "Idd_Book: " + book_.id() + ", Название: " + book_.title() + "\n";
            }

            // Выводим информацию о студенте и список его книг в новом окне
            QMessageBox::information(this, "Student Details", QString("Login: %1\n%2")
                                    .arg(student.get_login()).arg(book_list));
        });
    }
}


void Librarianform::on_Downloadimage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename, QString()) !=0){
        QImage image;
        bool valid = image.load(filename);

        if(valid){
          image = image.scaledToWidth( ui->Lbl_image->width(), Qt::SmoothTransformation);
          image = image.scaledToHeight( ui->Lbl_image->height(), Qt::SmoothTransformation);
          ui->Lbl_image->setPixmap(QPixmap::fromImage(image));
          ui->imagePathEdit->setText(filename);
        }
        else {
            QMessageBox::information(this, tr("Ошибка"),
                                     tr("Обложка не загруженна!"));
        }
    }
}

int globalID;

void loadGlobalID() {
    QFile file("globalID.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        globalID = 0;
        return;
    }

    QTextStream in(&file);
    globalID = in.readLine().toInt();
    file.close();
}

void saveGlobalID() {
    QFile file("globalID.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Can't save global ID!"));
        return;
    }

    QTextStream out(&file);
    out << globalID;
    file.close();
}

void Librarianform::on_createBookButton_clicked()
{
    QString title = ui->titleEdit->text();
    QString author = ui->autorEdit->text();
    QString genre = ui->genreEdit->text();
    QString link = ui->linkEdit->text();
    QString description = ui->DescriptionEdit->toPlainText();
    int quantity = ui->quantityBox->value();
    QString coverPath = ui->imagePathEdit->text();

    if(title.isEmpty() || author.isEmpty() || description.isEmpty() || quantity < 1 || coverPath.isEmpty()){
        QMessageBox::information(this, tr("Ошибка"),
                                 tr("Все поля должны быть заполнены и обложка должна быть выбрана!"));
    } else {
        loadGlobalID();
        Book newBook(QString::number(globalID), title, description, author, genre, coverPath, quantity, link); // Тут подразумевается, что у вас есть подходящий конструктор в классе Book
        globalID++;
        saveGlobalID();
        ui->titleEdit->clear();
        ui->autorEdit->clear();
        ui->genreEdit->clear();
        ui->linkEdit->clear();
        ui->DescriptionEdit->clear();
        ui->quantityBox->setValue(0);
        ui->imagePathEdit->clear();
        ui->Lbl_image->setPixmap(QPixmap());
        update_book_list();
    }
}

void Librarianform::on_searchButton_clicked() {

    QString author = ui->searchAutorEdit->text();
    QString title = ui->searchTitleEdit->text();
    qInfo() << author << title;

    update_book_list(author, title);
}
