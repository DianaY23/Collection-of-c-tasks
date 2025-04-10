# Система управления студентами и курсами

## Описание задачи

Необходимо разработать систему для управления студентами и курсами в университете. Система должна позволять добавлять студентов и курсы, а также регистрировать студентов на курсы, выводить список студентов на курсе и проверять, на какие курсы записан тот или иной студент.

## Требования

### Класс `Student` должен хранить информацию о студенте:
- Фамилия, имя, возраст.
- Уникальный идентификатор студента.

### Класс `Course` должен хранить информацию о курсе:
- Название курса.
- Уникальный идентификатор курса.
- Максимальное количество студентов, которые могут быть на курсе.

### Класс `UniversitySystem` должен управлять:
- Списком студентов.
- Списком курсов.
- Функцией для регистрации студентов на курсы (проверка на наличие мест на курсе).
- Функцией для отображения всех студентов, записанных на определённый курс.
- Функцией для вывода всех курсов, на которые записан студент.

## Программа должна позволять:
- Добавлять студентов и курсы.
- Регистрировать студентов на курсы.
- Проверять, какие студенты записаны на конкретный курс.
- Проверять, на какие курсы записан конкретный студент.
- В системе не должно быть дублирующихся студентов и курсов, то есть уникальность идентификаторов (ID) должна проверяться.

## Структура классов

### `Student`
Атрибуты:
- `string firstName` — имя.
- `string lastName` — фамилия.
- `int age` — возраст.
- `int studentId` — уникальный идентификатор студента.

Методы:
- Конструктор.
- Геттеры для атрибутов.
- Метод для вывода информации о студенте.

### `Course`
Атрибуты:
- `string courseName` — название курса.
- `int courseId` — уникальный идентификатор курса.
- `int maxStudents` — максимальное количество студентов на курсе.
- `vector<Student*> enrolledStudents` — список студентов, записанных на курс.

Методы:
- Конструктор.
- Геттеры для атрибутов.
- Метод для регистрации студента на курс.
- Метод для вывода всех студентов на курсе.

### `UniversitySystem`
Атрибуты:
- `vector<Student> students` — список всех студентов.
- `vector<Course> courses` — список всех курсов.

Методы:
- Метод для добавления студента.
- Метод для добавления курса.
- Метод для регистрации студента на курс.
- Метод для вывода студентов на курсе.
- Метод для вывода курсов студента.

## Дополнительные замечания
- Программа должна проверять наличие свободных мест на курсе перед тем, как записать студента.
- В системе могут быть различные курсы, и один студент может быть записан на несколько курсов.
- Студенты могут быть удалены из системы (например, в случае отчисления), и их данные должны быть корректно обновлены в базе данных курсов.

## Пример взаимодействия с системой

### Добавление студентов и курсов:
- Студент: Иванов Иван, 20 лет, ID: 1.
- Курс: Математика, ID: 101, макс. количество студентов: 30.

### Регистрация студента на курс:
- Студент Иванов Иван записывается на курс "Математика".

### Вывод студентов на курсе:
- "Математика": Студенты: Иванов Иван, Петров Петр, и т. д.

### Вывод курсов студента:
- Студент Иванов Иван записан на курсы: Математика, Физика.

### Удаление студента:
- Удаление студента из базы данных и из списка студентов на курсах.
