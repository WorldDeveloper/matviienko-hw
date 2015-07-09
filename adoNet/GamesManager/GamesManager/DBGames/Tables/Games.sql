CREATE TABLE [dbo].[Games] (
    [Id]              UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [Number]          INT              NOT NULL,
    [Team1]           UNIQUEIDENTIFIER NOT NULL,
    [Team2]           UNIQUEIDENTIFIER NOT NULL,
    [Result]          TINYINT          NOT NULL,
    [Team1BidPercent] TINYINT          NULL,
    [Team2BidPercent] TINYINT          NULL,
    [Date]            DATETIME2 (0)    NULL,
    [League]          UNIQUEIDENTIFIER NULL,
    [IsFinished]      BIT              DEFAULT ((0)) NOT NULL,
    CONSTRAINT [PK_Games] PRIMARY KEY CLUSTERED ([Id] ASC),
    UNIQUE NONCLUSTERED ([Number] ASC),
    CONSTRAINT [FK_Games_To_Teams1] FOREIGN KEY ([Team1]) REFERENCES [dbo].[Teams] ([Id]),
    CONSTRAINT [FK_Games_To_Teams2] FOREIGN KEY ([Team2]) REFERENCES [dbo].[Teams] ([Id]),
    CONSTRAINT [FK_Games_To_Leagues] FOREIGN KEY ([League]) REFERENCES [dbo].[Leagues] ([Id]),
    CONSTRAINT [CK_Games_Result] CHECK ([Result]>=(0) AND [Result]<=(2)),
    CONSTRAINT [CK_Games_TeamBids] CHECK (([Team1BidPercent]+[Team2BidPercent])=(100) AND [Team1BidPercent]>=(0) AND [Team2BidPercent]>=(0))
);

