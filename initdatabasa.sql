--create database busmanage;

use busmanage;

-- ������� ������� ��� �������� ���������� � ����� ���������
create table ���_��������(
	��������_����_�������� nvarchar(50) primary key clustered,
	�����_����������� int not null check( �����_����������� > 0),
	�������_���� int not null,
	constraint �����������_cst check(�������_���� <= �����_����������� and �������_���� >= 0 )
	)
	go
-- ������� ������� ��� �������� ���������� � ����
create table ����(
	�����_���� int primary key clustered,
	����������� int not null check(����������� > 0),
	����������_�������� int not null check(����������_�������� >= 0)
	)
	go

-- ������� ������� ��� �������� ���������� � ���������
create table �������(
	���_����� nvarchar(10) primary key clustered check(len(���_�����)>=6),
	��������_����� nvarchar(5),
	��������_����_�������� nvarchar(50) not null foreign key references ���_��������(��������_����_��������),
	�����_���� int not null foreign key references ����(�����_����)
	)
	go
-- ������� ������� ��� �������� ���������� � ���������
create table �������(
	�����_�������� nvarchar(5) primary key clustered check(len(�����_��������)>0),
	�����_�������� float check( �����_�������� > 0 )
	)
	go

-- ������� ������� ��� �������� ���������� � ����������
create table ���������(
	��_��������� int identity primary key clustered,
	��������_��������� nvarchar(50) not null
	)
	go

-- ������� ������� ��� �������� ���������� � ���������� ���������
create table ���������_��������(
	�����_�������� nvarchar(5) not null foreign key references �������(�����_��������),
	��_��������� int not null foreign key references ���������(��_���������),
	constraint primkey_���������_�������� primary key clustered(�����_��������, ��_���������)
	)
	go

-- ������� ������� ��� �������� ���������� � ������
create table ����(
	�����_��������_����� nvarchar(12) primary key clustered check(len(�����_��������_�����)<12),
	���_����� nvarchar(10) not null foreign key references ������� (���_�����),
	�����_�������� nvarchar(5) not null foreign key references ������� (�����_��������),
	����_����� DATE not null default (getDate())
	)
	go

-- ������� ������� ��� �������� ���������� � ����������� �� ���������
create table �����������_��_��������(
	��_�����������_�������� int identity primary key clustered,
	��_��������� int not null foreign key references ���������(��_���������),
	�����_��������_����� nvarchar(12) not null foreign key references ����(�����_��������_�����),
	�����_�������� time not null,
	�����_������� time,
	constraint �����_cst check(�����_�������� < �����_�������)
	)
	go

-- ������� ������� ��� �������� ���������� � ����������
create table ���������(
	��������_��������� nvarchar(25)  primary key clustered check(len(��������_���������)>0),
	����� money not null check(����� > 0)
	)
	go

-- ������� ������� ��� �������� ���������� � ����������
create table ��������(
	���_��������� nvarchar(12) primary key clustered check(len(���_���������)=12),
	������� nvarchar(25) not null,
	��� nvarchar(25) not null,
	�������� nvarchar(25),
	��������_��������� nvarchar(25) not null foreign key references ���������(��������_���������),
	���������� image,
	����_����� DATE not null default(getDate()),
	����_���������� DATE
	)
	go
-- ������� ������� ��� �������� ���������� � ���������� �� �����
create table ��������_��_�����(
	��_����� int identity primary key clustered,
	�����_��������_����� nvarchar(12) not null foreign key references ���� (�����_��������_�����),
	���_��������� nvarchar(12) not null foreign key references �������� (���_���������)
	)
	go

-- ������� ������ � ������� ���_��������
-- ���������: ���������, �������� (���� ��������), ����� �����������, ������� ����
create procedure ��������_���_��������
	@Result nvarchar(50) output,
	@���� nvarchar(50),
	@�� int,
	@�� int
AS
BEGIN
	-- ���� ���������� ������
	if exists(select * from ���_�������� where ��������_����_�������� = @����)
	BEGIN
		select '������: ����� ��� ��� ����: ' + @����
		return
	END
	-- ���� �� ������������� ������� �����������
	-- ����� ���� ������ ��� ������� � ������� ���� ������ ����
	if @�� < @�� and @��>=0
	BEGIN
		select '������: ���. ����. ����. ��� ���. ����. � ' + @����
		return
	END
	
	INSERT INTO ���_��������(��������_����_��������, �����_�����������, �������_����) values (@����, @��, @��)
	-- �������� �� �������� �������
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	
	return
END
GO

-- ��������� ��� ������� ������ � ������� ����
-- ���������: OUT ��������, ����� - ����� ����, ����������� - ����������� ����, ������� - ���������� �������� � ����
create procedure ��������_����
	@OUT nvarchar(50) output,
	@����� int,
	@����������� int,
	@������� int
AS
BEGIN
	if exists(select * from ���� where �����_���� = @�����)
	BEGIN
		select '��� ���� ���� � ����� �������'
		return
	END
	insert into ����(�����_����, �����������, ����������_��������) values (@�����, @�����������, @�������)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

-- ��������� ��� ������� ������ � ������� �������
create procedure ��������_�������
	@OUT nvarchar(50) output,
	@���_����� nvarchar(10),
	@���_����� nvarchar(5),
	@��� nvarchar(50),
	@�����_���� int
AS
BEGIN
	if exists(select * from ������� where ���_����� = @���_�����)
	BEGIN
		select '������: ����� ������� ��� ����: ' + str(@���_�����)
		return
	END
	if not exists(select * from ���_�������� where ��������_����_�������� = @���)
	BEGIN
	    Select '������: ��� ������ ���� ��������: ' + @���
		return
	END
	if not exists(select * from ���� where �����_���� = @�����_����)
	BEGIN
		select '������: ��� ������ ����: ' + str(@�����_����)
		return
	END
	insert into �������(���_�����, ��������_�����, ��������_����_��������, �����_����) values(@���_�����, @���_�����, @���, @�����_����)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return	
END
GO

create procedure ��������_���������
	@OUT nvarchar(50) output,
	@�������� nvarchar(25),
	@����� money
AS
BEGIN
	if exists(select * from ��������� where ��������_��������� = @��������)
	BEGIN
		select '������: ��� ���� ����� ���������'
		return
	END
	insert into ���������(��������_���������, �����) values(@��������, @�����)
	if @@ROWCOUNT > 0 
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
END
GO

create procedure ��������_���������
	@OUT nvarchar(50) output,
	@��� nvarchar(12),
	@������� nvarchar(25),
	@��� nvarchar(25),
	@�������� nvarchar(25),
	@��������� nvarchar(25),
	@���������� image,
	@����_����� date,
	@����_���������� date
AS
BEGIN
	if exists(select * from �������� where ���_��������� = @���)
	BEGIN
		select '������: �������� � ���� ��� ��� ����'
		return
	END
	if LEN(@���)!=12
	BEGIN
		select '������: ��� �� ����� (!=12 ����)'
		return
	END
	if @����_���������� is not null
	BEGIN
		if @����_����� > @����_����������
		BEGIN
			select '������: ���� ����� ����� ���� ����������'
			return
		END
	END
	if not exists(select * from ��������� where ��������_��������� = @���������)
	BEGIN
		select '������: ��� ����� ���������'
		return
	END
	insert into ��������(���_���������, �������, ���, ��������, ��������_���������, ����������, ����_�����, ����_����������)
	values (@���, @�������, @���, @��������, @���������, @����������, @����_�����, @����_����������) 
END
GO

create procedure ��������_���������
	@OUT nvarchar(50) output,
	@��������_��������� nvarchar(50)
AS
BEGIN
	insert into ���������(��������_���������) values(@��������_���������)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

create procedure ��������_�������
	@OUT nvarchar(50) output,
	@����� nvarchar(5),
	@����� float
AS
BEGIN
	if exists(select * from ������� where �����_�������� =  @�����)
	BEGIN
		select '������: ����� ������� ��� ����'
		return
	END
	insert into �������(�����_��������, �����_��������) values(@�����, @�����)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

create procedure ��������_���������_��������
	@OUT nvarchar(50) output,
	@�����_�������� nvarchar(5),
	@��������� int
AS
BEGIN
	if exists(select * from ���������_�������� where �����_�������� = @�����_��������
		and ��_��������� = @���������)
	BEGIN
		select '������: ����� ��������� �������� ��� ����'
		return	
	END
	if not exists(select * from ��������� where ��_��������� = @���������)
	BEGIN
		select '������: ��� ����� ���������'
		return
	END
	if not exists(select * from ������� where �����_�������� = @�����_��������)
	BEGIN
		select '������: ��� ������ ��������'
		return
	END
	insert into ���������_��������(�����_��������,��_���������) values(@�����_��������, @���������)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

create procedure ��������_����
	@OUT nvarchar(50) output,
	@�����_���_����� nvarchar(12),
	@���_�����_�������� nvarchar(10),
	@�����_�������� nvarchar(5),
	@����_����� DATE
AS
BEGIN
	if exists(select * from ���� where �����_��������_����� = @�����_���_�����)
	BEGIN
		select '������: ���� � ����� ��� ��� ����'
		return
	END
	if not exists(select * from ������� where ���_����� = @���_�����_��������)
	BEGIN
		select '������: �������� � ����� ������� ���'
		return
	END
	if not exists(select * from ������� where �����_�������� = @�����_��������)
	BEGIN
		select '������: ������ �������� ���'
		return
	END
	insert into ����(�����_��������_�����, ���_�����, �����_��������, ����_�����) 
	values (@�����_���_�����, @���_�����_��������, @�����_��������, @����_�����)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

create procedure ��������_�����������_��_��������
	@OUT nvarchar(50) output,
	@��������� int,
	@�����_���_����� nvarchar(12),
	@�����_�������� TIME,
	@�����_������� TIME
AS
BEGIN
	if not exists(select * from ��������� where ��_��������� = @���������)
	BEGIN
		select '������: ��� ���������'
		return
	END
	if not exists(select * from ���� where �����_��������_����� = @�����_���_�����)
	BEGIN
		select '������: ��� ��������'
		return
	END
	if   @�����_������� is not null
	BEGIN
		if @�����_�������� > @�����_�������
		BEGIN
			select '������: ����� �������� ����� �������'
			return
		END
	END 
	insert into �����������_��_��������(��_���������, �����_��������_�����, �����_��������, �����_�������)
	values(@���������, @�����_���_�����, @�����_��������, @�����_�������)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO

create procedure ��������_�����_��������_���
	@OUT nvarchar(50) output,
	@����� TIME,
	@��_�����������_��_�������� int
AS
BEGIN
	if exists(select * from �����������_��_�������� where ��_�����������_�������� = @��_�����������_��_��������)
	BEGIN
		if @����� is not null
		BEGIN
			update �����������_��_�������� set �����_������� = @�����
				where ��_�����������_�������� = @��_�����������_��_��������
		END
		ELSE
		BEGIN
			update �����������_��_�������� set �����_������� = GETDATE()
				where ��_�����������_�������� = @��_�����������_��_��������
		END	
	END
	ELSE
	BEGIN
		select '������: ��� ������ �����������'
		return
	END
	select '����� ������� ������� ����������'
END
GO

create procedure ��������_���������_��_�����
	@OUT nvarchar(50) output,
	@�����_���_����� nvarchar(12),
	@���_�������� nvarchar(12)
AS
BEGIN
	if not exists(select * from ���� where �����_��������_����� = @�����_���_�����)
	BEGIN
		select '������: ��� ������ �����'
		return
	END
	if not exists(select * from �������� where ���_��������� = @���_��������)
	BEGIN
		select '������: ��� ������ ���������'
		return
	END
	insert into ��������_��_�����(�����_��������_�����, ���_���������) values (@�����_���_�����, @���_��������)
	if @@ROWCOUNT > 0
	BEGIN
		select '���������: ����� ���������'
		return
	END
	ELSE
	BEGIN
		select '������: ������� � ������� ���������'
	END
	return
END
GO