use busmanage;
go
create view ����������_�_����� as
	select
	   ����.�����_��������_�����,
	   ��������.������� + ' ' + ��������.��� as [��������],
	   ��������.��������_���������,
       ����.���_�����,
       �������.��������_����_��������,
       ���_��������.�����_�����������,
       ����_�����
		from ���� 
			join ������� On �������.���_����� =  ����.���_�����
			join ���_�������� on ���_��������.��������_����_�������� = �������.��������_����_��������
			join ��������_��_����� on ��������_��_�����.�����_��������_����� = ����.�����_��������_�����
			join �������� on ��������.���_��������� = ��������_��_�����.���_���������
go

create view ����������_�_���������� as
select
	��������.������� + ' ' + ��������.��� + ' ' +isnull(��������.��������,'') as [��������],
	��������.��������_���������,
	���������.�����,
	��������.����_�����,
	��������.����_����������
		from ��������
			join ��������� on ���������.��������_��������� = ��������.��������_���������
go

create view ����������_�_������������ as
select
	�����������_��_��������.��_�����������_�������� as [������],
	���������.��������_���������,
	�����������_��_��������.�����_��������,
	�����������_��_��������.�����_�������,
	����.���_�����,
	����.�����_��������,
	����.����_�����
		from �����������_��_��������
			join ��������� on ���������.��_��������� = �����������_��_��������.��_���������
			join ���� on ����.�����_��������_����� = �����������_��_��������.�����_��������_�����
go

create view ����������_�_���� as
select 
	����.�����_����,
	�����������,
	����������_��������,
	�������.���_�����,
	�������.��������_����_��������
		from ����
			join ������� on �������.�����_���� = ����.�����_����
go