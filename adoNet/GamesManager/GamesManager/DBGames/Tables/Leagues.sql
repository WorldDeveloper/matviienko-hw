CREATE TABLE [dbo].[Leagues] (
    [Id]         UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [Name]       NVARCHAR (50)    NOT NULL,
    [PictureUrl] NVARCHAR (MAX)   NULL,
    CONSTRAINT [PK_Leagues] PRIMARY KEY CLUSTERED ([Id] ASC)
);

