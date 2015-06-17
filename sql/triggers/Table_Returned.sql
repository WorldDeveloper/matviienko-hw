USE Library;
go

CREATE TABLE Returned
(
	Id INT IDENTITY PRIMARY KEY,
	FirstName nvarchar(15) not null,
	LastName nvarchar(25) not null,
	BookTitle nvarchar(100) not null,
	DateIn date not null
)