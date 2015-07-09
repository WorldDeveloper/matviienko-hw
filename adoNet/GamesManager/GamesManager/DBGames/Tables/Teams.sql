CREATE TABLE [dbo].[Teams] (
    [Id]         UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [Name]       NVARCHAR (50)    NOT NULL,
    [Wins]       SMALLINT         DEFAULT ((0)) NOT NULL,
    [Losses]     SMALLINT         DEFAULT ((0)) NOT NULL,
    [Draws]      SMALLINT         DEFAULT ((0)) NOT NULL,
    [PictureUrl] NVARCHAR (MAX)   NULL,
    CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED ([Id] ASC),
    CONSTRAINT [CK_Teams_Wins] CHECK ([Wins]>=(0)),
    CONSTRAINT [CK_Teams_Loses] CHECK ([Losses]>=(0)),
    CONSTRAINT [CK_Teams_Draws] CHECK ([Draws]>=(0))
);

