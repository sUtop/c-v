# c-v
c-v это тестовая программа, имеющая 2 модуля:
 * server - серверная часть приложения
 * viewer - клиентская часть приложения

Серверная часть приложения имеет 3 части:
 * Generator - генерирует случайные пиксели
 * MessageSender - отправляет сгенерированные данные клиенту
 * MessageClient - получает запросы от клиента для генерации

MessageSender и MessageClient запускаются в различных потоках,
связь между ними осуществляется через локальную переменную 
request. MessageClient - ждет подключения клиента на порт
7777, когда клиент подключился тут же происходит получение 
запросов от пользователя на отображение строк. MessageSender 
генерирует ответы для пользователя (используя при этом 
Generator) и отсылает их на порт 8888.

Клиентская часть приложения имеет 3 части : 
 * MessageClient - получает данные для отрисовки
 * MessageAnswer - отсылает заявки на отображение
 * Widget - отображение полученной информации

MessageClient и MessageAnswer запускаются в отдельных потоках
Widget запускается в главном потоке. Как только клиентская 
часть запустилась MessageAnswer пытается подключиться на порт 
7777 и направить последовательность запросов отображения 
(от 1-ой линии пикселей до 720-ой). В это время MessageClient
ждет от сервера сообщений для отображения. Как только он 
получает один экран информации - он генерирует сигнал pixelsFull,
который принимает Widget и отображает полученный набор пикселей.