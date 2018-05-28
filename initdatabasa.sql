--create database busmanage;

use busmanage;

-- Создать таблицу для хранения информации о типах автобусов
create table тип_автобуса(
	название_типа_автобуса nvarchar(50) primary key clustered,
	общая_вместимость int not null check( общая_вместимость > 0),
	сидячих_мест int not null,
	constraint вместимость_cst check(сидячих_мест <= общая_вместимость and сидячих_мест >= 0 )
	)
	go
-- Создать таблицу для хранения информации о депо
create table депо(
	номер_депо int primary key clustered,
	вместимость int not null check(вместимость > 0),
	количество_техников int not null check(количество_техников >= 0)
	)
	go

-- Создать таблицу для хранения информации о автобусах
create table автобус(
	гос_номер nvarchar(10) primary key clustered check(len(гос_номер)>=6),
	гаражный_номер nvarchar(5),
	название_типа_автобуса nvarchar(50) not null foreign key references тип_автобуса(название_типа_автобуса),
	номер_депо int not null foreign key references депо(номер_депо)
	)
	go
-- Создать таблицу для хранения информации о маршрутах
create table маршрут(
	номер_маршрута nvarchar(5) primary key clustered check(len(номер_маршрута)>0),
	длина_маршрута float check( длина_маршрута > 0 )
	)
	go

-- Создать таблицу для хранения информации о остановках
create table остановка(
	ид_остановки int identity primary key clustered,
	название_остановки nvarchar(50) not null
	)
	go

-- Создать таблицу для хранения информации о остановках маршрутов
create table остановка_маршрута(
	номер_маршрута nvarchar(5) not null foreign key references маршрут(номер_маршрута),
	ид_остановки int not null foreign key references остановка(ид_остановки),
	constraint primkey_остановка_маршрута primary key clustered(номер_маршрута, ид_остановки)
	)
	go

-- Создать таблицу для хранения информации о рейсах
create table рейс(
	номер_путевого_листа nvarchar(12) primary key clustered check(len(номер_путевого_листа)<12),
	гос_номер nvarchar(10) not null foreign key references автобус (гос_номер),
	номер_маршрута nvarchar(5) not null foreign key references маршрут (номер_маршрута),
	дата_рейса DATE not null default (getDate())
	)
	go

-- Создать таблицу для хранения информации о перемещниях по маршрутам
create table перемещение_по_маршруту(
	ид_перемещение_маршруту int identity primary key clustered,
	ид_остановки int not null foreign key references остановка(ид_остановки),
	номер_путевого_листа nvarchar(12) not null foreign key references рейс(номер_путевого_листа),
	время_прибытия time not null,
	время_отбытия time,
	constraint время_cst check(время_прибытия < время_отбытия)
	)
	go

-- Создать таблицу для хранения информации о должностях
create table должности(
	название_должности nvarchar(25)  primary key clustered check(len(название_должности)>0),
	оклад money not null check(оклад > 0)
	)
	go

-- Создать таблицу для хранения информации о работниках
create table работник(
	ИНН_работника nvarchar(12) primary key clustered check(len(ИНН_работника)=12),
	фамилия nvarchar(25) not null,
	имя nvarchar(25) not null,
	отчество nvarchar(25),
	название_должности nvarchar(25) not null foreign key references должности(название_должности),
	фотография image,
	дата_наема DATE not null default(getDate()),
	дата_увольнения DATE
	)
	go
-- Создать таблицу для хранения информации о работниках на рейсе
create table работник_на_рейсе(
	ид_смены int identity primary key clustered,
	номер_путевого_листа nvarchar(12) not null foreign key references рейс (номер_путевого_листа),
	ИНН_работника nvarchar(12) not null foreign key references работник (ИНН_работника)
	)
	go

-- Вставка данных в таблицу тип_автобуса
-- аргументы: результат, название (типа автобуса), общая вместимость, сидячих мест
create procedure Вставить_тип_автобуса
	@Result nvarchar(50) output,
	@Назв nvarchar(50),
	@ОВ int,
	@СМ int
AS
BEGIN
	-- Если существует запись
	if exists(select * from тип_автобуса where название_типа_автобуса = @Назв)
	BEGIN
		select 'Ошибка: такой тип уже есть: ' + @Назв
		return
	END
	-- Если не удовлетворяет условию целостности
	-- Общих мест меньше чем сидячих и сидячих мест меньше нуля
	if @ОВ < @СМ and @СМ>=0
	BEGIN
		select 'Ошибка: общ. вмес. менш. чем сид. мест. В ' + @Назв
		return
	END
	
	INSERT INTO тип_автобуса(название_типа_автобуса, общая_вместимость, сидячих_мест) values (@Назв, @ОВ, @СМ)
	-- Проверка на успешную вставку
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	
	return
END
GO

-- Процедура для вставки записи в таблицу депо
-- аргументы: OUT выходной, номер - номер депо, вместимость - вместимость депо, техники - количество техников в депо
create procedure Вставить_депо
	@OUT nvarchar(50) output,
	@номер int,
	@вместимость int,
	@техники int
AS
BEGIN
	if exists(select * from депо where номер_депо = @номер)
	BEGIN
		select 'Уже есть депо с таким номером'
		return
	END
	insert into депо(номер_депо, вместимость, количество_техников) values (@номер, @вместимость, @техники)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

-- Процедура для вставки данных в таблицу Автобус
create procedure Вставить_автобус
	@OUT nvarchar(50) output,
	@Гос_Номер nvarchar(10),
	@Гар_Номер nvarchar(5),
	@тип nvarchar(50),
	@Номер_депо int
AS
BEGIN
	if exists(select * from автобус where гос_номер = @Гос_Номер)
	BEGIN
		select 'Ошибка: такой автобус уже есть: ' + str(@Гос_Номер)
		return
	END
	if not exists(select * from тип_автобуса where название_типа_автобуса = @тип)
	BEGIN
	    Select 'Ошибка: нет такого типа автобуса: ' + @тип
		return
	END
	if not exists(select * from депо where номер_депо = @Номер_депо)
	BEGIN
		select 'Ошибка: нет такого депо: ' + str(@Номер_депо)
		return
	END
	insert into автобус(гос_номер, гаражный_номер, название_типа_автобуса, номер_депо) values(@Гос_Номер, @Гар_Номер, @тип, @Номер_депо)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return	
END
GO

create procedure Вставить_должность
	@OUT nvarchar(50) output,
	@Название nvarchar(25),
	@Оклад money
AS
BEGIN
	if exists(select * from должности where название_должности = @Название)
	BEGIN
		select 'Ошибка: уже есть такая должность'
		return
	END
	insert into должности(название_должности, оклад) values(@Название, @Оклад)
	if @@ROWCOUNT > 0 
	BEGIN
		select 'Сообщение: успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
END
GO

create procedure Вставить_работника
	@OUT nvarchar(50) output,
	@ИНН nvarchar(12),
	@Фамилия nvarchar(25),
	@Имя nvarchar(25),
	@Отчество nvarchar(25),
	@должность nvarchar(25),
	@Фотография image,
	@дата_наема date,
	@дата_увольнения date
AS
BEGIN
	if exists(select * from работник where ИНН_работника = @ИНН)
	BEGIN
		select 'Ошибка: Работник с этим ИНН уже есть'
		return
	END
	if LEN(@ИНН)!=12
	BEGIN
		select 'Ошибка: ИНН не верен (!=12 цифр)'
		return
	END
	if @дата_увольнения is not null
	BEGIN
		if @дата_наема > @дата_увольнения
		BEGIN
			select 'Ошибка: дата наема позже даты увольнения'
			return
		END
	END
	if not exists(select * from должности where название_должности = @должность)
	BEGIN
		select 'Ошибка: нет такой должности'
		return
	END
	insert into работник(ИНН_работника, фамилия, имя, отчество, название_должности, фотография, дата_наема, дата_увольнения)
	values (@ИНН, @Фамилия, @Имя, @Отчество, @должность, @Фотография, @дата_наема, @дата_увольнения) 
END
GO

create procedure Вставить_остановка
	@OUT nvarchar(50) output,
	@Название_остановки nvarchar(50)
AS
BEGIN
	insert into остановка(название_остановки) values(@Название_остановки)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

create procedure Вставить_маршрут
	@OUT nvarchar(50) output,
	@Номер nvarchar(5),
	@длина float
AS
BEGIN
	if exists(select * from маршрут where номер_маршрута =  @Номер)
	BEGIN
		select 'Ошибка: Такой маршрут уже есть'
		return
	END
	insert into маршрут(номер_маршрута, длина_маршрута) values(@Номер, @длина)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

create procedure Вставить_остановку_маршрута
	@OUT nvarchar(50) output,
	@номер_маршрута nvarchar(5),
	@остановка int
AS
BEGIN
	if exists(select * from остановка_маршрута where номер_маршрута = @номер_маршрута
		and ид_остановки = @остановка)
	BEGIN
		select 'Ошибка: такая остановка маршрута уже есть'
		return	
	END
	if not exists(select * from остановка where ид_остановки = @остановка)
	BEGIN
		select 'Ошибка: нет такой остановки'
		return
	END
	if not exists(select * from маршрут where номер_маршрута = @номер_маршрута)
	BEGIN
		select 'Ошибка: нет такого маршрута'
		return
	END
	insert into остановка_маршрута(номер_маршрута,ид_остановки) values(@номер_маршрута, @остановка)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

create procedure Вставить_Рейс
	@OUT nvarchar(50) output,
	@номер_пут_листа nvarchar(12),
	@гос_номер_автобуса nvarchar(10),
	@номер_маршрута nvarchar(5),
	@Дата_рейса DATE
AS
BEGIN
	if exists(select * from рейс where номер_путевого_листа = @номер_пут_листа)
	BEGIN
		select 'Ошибка: Рейс с таким НПЛ уже есть'
		return
	END
	if not exists(select * from автобус where гос_номер = @гос_номер_автобуса)
	BEGIN
		select 'Ошибка: автобуса с таким номером нет'
		return
	END
	if not exists(select * from маршрут where номер_маршрута = @номер_маршрута)
	BEGIN
		select 'Ошибка: такого маршрута нет'
		return
	END
	insert into рейс(номер_путевого_листа, гос_номер, номер_маршрута, дата_рейса) 
	values (@номер_пут_листа, @гос_номер_автобуса, @номер_маршрута, @Дата_рейса)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

create procedure Вставить_перемещение_по_маршруту
	@OUT nvarchar(50) output,
	@остановка int,
	@номер_пут_листа nvarchar(12),
	@Время_прибытия TIME,
	@время_отбытия TIME
AS
BEGIN
	if not exists(select * from остановка where ид_остановки = @остановка)
	BEGIN
		select 'Ошибка: нет остановки'
		return
	END
	if not exists(select * from рейс where номер_путевого_листа = @номер_пут_листа)
	BEGIN
		select 'Ошибка: нет маршрута'
		return
	END
	if   @время_отбытия is not null
	BEGIN
		if @Время_прибытия > @время_отбытия
		BEGIN
			select 'Ошибка: время прибытия позже отбытия'
			return
		END
	END 
	insert into перемещение_по_маршруту(ид_остановки, номер_путевого_листа, время_прибытия, время_отбытия)
	values(@остановка, @номер_пут_листа, @Время_прибытия, @время_отбытия)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO

create procedure Вставить_время_прибытия_ППМ
	@OUT nvarchar(50) output,
	@время TIME,
	@ид_перемещения_по_маршруту int
AS
BEGIN
	if exists(select * from перемещение_по_маршруту where ид_перемещение_маршруту = @ид_перемещения_по_маршруту)
	BEGIN
		if @время is not null
		BEGIN
			update перемещение_по_маршруту set время_отбытия = @время
				where ид_перемещение_маршруту = @ид_перемещения_по_маршруту
		END
		ELSE
		BEGIN
			update перемещение_по_маршруту set время_отбытия = GETDATE()
				where ид_перемещение_маршруту = @ид_перемещения_по_маршруту
		END	
	END
	ELSE
	BEGIN
		select 'Ошибка: нет такого перемещения'
		return
	END
	select 'Время отбытия успешно обновленно'
END
GO

create procedure Вставить_работника_на_рейсе
	@OUT nvarchar(50) output,
	@номер_пут_листа nvarchar(12),
	@ИНН_Рабтника nvarchar(12)
AS
BEGIN
	if not exists(select * from рейс where номер_путевого_листа = @номер_пут_листа)
	BEGIN
		select 'Ошибка: нет такого рейса'
		return
	END
	if not exists(select * from работник where ИНН_работника = @ИНН_Рабтника)
	BEGIN
		select 'Ошибка: нет такого работника'
		return
	END
	insert into работник_на_рейсе(номер_путевого_листа, ИНН_работника) values (@номер_пут_листа, @ИНН_Рабтника)
	if @@ROWCOUNT > 0
	BEGIN
		select 'Сообщение: Успех процедуры'
		return
	END
	ELSE
	BEGIN
		select 'Ошибка: Вставка в таблицу неудалась'
	END
	return
END
GO