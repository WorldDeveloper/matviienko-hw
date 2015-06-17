USE [library]
GO

CREATE TABLE Issued
(
	[Id] [int] IDENTITY(1,1) NOT NULL PRIMARY KEY,
	[VisitorName] [nvarchar](15) NOT NULL,
	[VisitorSurname] [nvarchar](25) NOT NULL,
	[BookTitle] [nvarchar](100) NOT NULL,
	[DateOut] [date] NOT NULL,
)

