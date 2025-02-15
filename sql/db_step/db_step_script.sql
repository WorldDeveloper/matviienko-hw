USE [master]
GO
/****** Object:  Database [Step]    Script Date: 19.06.2015 16:46:22 ******/
CREATE DATABASE [Step]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Step', FILENAME = N'D:\GitHub\step-homeworks\sql\db_step\Step.mdf' , SIZE = 4288KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'Step_log', FILENAME = N'D:\GitHub\step-homeworks\sql\db_step\Step_log.ldf' , SIZE = 1072KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [Step] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Step].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Step] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Step] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Step] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Step] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Step] SET ARITHABORT OFF 
GO
ALTER DATABASE [Step] SET AUTO_CLOSE ON 
GO
ALTER DATABASE [Step] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Step] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Step] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Step] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Step] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Step] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Step] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Step] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Step] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Step] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Step] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Step] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Step] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Step] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Step] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Step] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Step] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [Step] SET  MULTI_USER 
GO
ALTER DATABASE [Step] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Step] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Step] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Step] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
ALTER DATABASE [Step] SET DELAYED_DURABILITY = DISABLED 
GO
USE [Step]
GO
/****** Object:  Table [dbo].[Addresses]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Addresses](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Country] [nvarchar](50) NOT NULL,
	[Locality] [nvarchar](100) NOT NULL,
	[Street] [nvarchar](100) NOT NULL,
	[HouseNumber] [nvarchar](20) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Courses]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Courses](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[SubjectId] [int] NOT NULL,
	[TeacherId] [int] NOT NULL,
	[StartDate] [date] NOT NULL,
	[Hours] [int] NOT NULL,
	[GroupId] [int] NOT NULL,
 CONSTRAINT [PK__Course__3214EC076BDF8738] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Departments]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Departments](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ExaminationRolls]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ExaminationRolls](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ExamDate] [date] NOT NULL,
	[TeacherId] [int] NOT NULL,
	[CourseId] [int] NOT NULL,
 CONSTRAINT [PK__Examinat__3214EC07E1463356] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ExaminationRollsLines]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ExaminationRollsLines](
	[ExaminationRollID] [int] NOT NULL,
	[StudentId] [int] NOT NULL,
	[Mark] [tinyint] NOT NULL,
 CONSTRAINT [PK_ExaminationRollsLines] PRIMARY KEY CLUSTERED 
(
	[ExaminationRollID] ASC,
	[StudentId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Groups]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Groups](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](30) NOT NULL,
	[FormId] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[LearningForms]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LearningForms](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Lessons]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Lessons](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ExecutionDate] [date] NOT NULL,
	[PairNumber] [tinyint] NOT NULL,
	[RoomId] [int] NOT NULL,
	[CourseId] [int] NOT NULL,
 CONSTRAINT [PK__Lessons__3214EC07629C7788] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[LessonsDetails]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LessonsDetails](
	[LessonId] [int] NOT NULL,
	[StudentId] [int] NOT NULL,
	[StudentPresence] [bit] NOT NULL,
	[ClassMark] [tinyint] NOT NULL,
	[HomeMark] [tinyint] NOT NULL,
	[Note] [nvarchar](100) NULL,
 CONSTRAINT [PK_LessonsDetails] PRIMARY KEY CLUSTERED 
(
	[LessonId] ASC,
	[StudentId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Notes]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Notes](
	[Id] [int] NOT NULL,
	[Note] [nvarchar](max) NOT NULL,
 CONSTRAINT [PK__Notes__3214EC076ED7C006] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Persons]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Persons](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[LastName] [nvarchar](100) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[Patronymic] [nvarchar](50) NULL,
	[BirthDay] [date] NULL,
	[AddressId] [int] NULL,
	[PhotoId] [int] NULL,
	[NoteId] [int] NULL,
 CONSTRAINT [PK__Person__3214EC07E62A7EA1] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[PhoneNumbers]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PhoneNumbers](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[PhoneNumber] [nvarchar](20) NOT NULL,
	[PersonId] [int] NOT NULL,
 CONSTRAINT [PK__PhoneNum__3214EC07D68D4E0E] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Photos]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Photos](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Photo] [varbinary](max) NOT NULL,
 CONSTRAINT [PK_Photos] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Rooms]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Rooms](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Number] [char](3) NOT NULL,
	[RoomsTypeId] [int] NULL,
	[ComputersNumber] [int] NOT NULL,
	[ConferenceHall] [bit] NOT NULL DEFAULT ((0)),
	[IsEducational] [bit] NOT NULL,
	[Note] [nvarchar](100) NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[RoomsType]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[RoomsType](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](20) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Seasons]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Seasons](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](10) NOT NULL,
 CONSTRAINT [PK_Seasons] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Specializations]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Specializations](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Streams]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Streams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Year] [char](4) NOT NULL,
	[SeasonId] [int] NOT NULL,
 CONSTRAINT [PK__Streams__3214EC0779474618] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Students]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Students](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[PersonId] [int] NOT NULL,
	[GroupId] [int] NOT NULL,
	[StreamId] [int] NOT NULL,
	[SpecializationId] [int] NOT NULL,
 CONSTRAINT [PK__Student__3214EC07C9D71198] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Subjects]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Subjects](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](100) NOT NULL,
	[DepartmentId] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Teachers]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teachers](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[PersonId] [int] NOT NULL,
	[DepartmentId] [int] NOT NULL,
 CONSTRAINT [PK__Teachers__3214EC07C8EE3353] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Users]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] NOT NULL,
	[Login] [nvarchar](50) NOT NULL,
	[Password] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK__Logins__3214EC07254434D5] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  View [dbo].[v_students]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE view [dbo].[v_students]
AS
select students.Id, FirstName, LastName, Groups.Name AS [Group]
from persons join students ON persons.Id=students.PersonId JOIN Groups ON students.GroupId=Groups.Id;


GO
/****** Object:  View [dbo].[v_StudentsMarks]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE view [dbo].[v_StudentsMarks]
as
select   Groups.Name AS [Group], v_Students.FirstName, v_Students.LastName, Subjects.Name AS [Subject]
from courses JOIN subjects ON courses.SubjectId=subjects.Id 
JOIN Groups ON courses.GroupId=Groups.Id
JOIN v_Students ON Groups.Id=v_Students.Id

GO
/****** Object:  View [dbo].[v_teachers]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[v_teachers]
AS
select teachers.Id, FirstName, LastName, departmentId
from persons join teachers ON persons.Id=teachers.PersonId;
GO
/****** Object:  View [dbo].[v_courses]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[v_courses]
as
select Courses.Id, Subjects.Name AS [Subject], v_Teachers.FirstName, v_Teachers.Lastname, Groups.Name AS [Group], StartDate, Hours
from courses JOIN subjects ON courses.SubjectId=subjects.Id 
JOIN v_teachers ON courses.TeacherId=v_teachers.Id 
JOIN Groups ON courses.GroupId=Groups.Id;
GO
/****** Object:  View [dbo].[v_TimeTable]    Script Date: 19.06.2015 16:46:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[v_TimeTable]
as
select ExecutionDate AS [Date], PairNumber AS [Pair], Rooms.Number as Room, [Subject], Firstname + LastName AS Teacher, v_courses.[Group] 
from lessons join v_courses ON lessons.CourseId=v_courses.Id
	JOIN Rooms ON lessons.RoomId=Rooms.Id
GO
SET IDENTITY_INSERT [dbo].[Addresses] ON 

INSERT [dbo].[Addresses] ([Id], [Country], [Locality], [Street], [HouseNumber]) VALUES (1, N'Ukraine', N'Odesa', N'Yevreyska', N'3')
INSERT [dbo].[Addresses] ([Id], [Country], [Locality], [Street], [HouseNumber]) VALUES (2, N'Ukraine', N'Kyiv', N'Bankova', N'1')
SET IDENTITY_INSERT [dbo].[Addresses] OFF
SET IDENTITY_INSERT [dbo].[Courses] ON 

INSERT [dbo].[Courses] ([Id], [SubjectId], [TeacherId], [StartDate], [Hours], [GroupId]) VALUES (3, 1, 3, CAST(N'2014-02-01' AS Date), 100, 3)
INSERT [dbo].[Courses] ([Id], [SubjectId], [TeacherId], [StartDate], [Hours], [GroupId]) VALUES (4, 2, 2, CAST(N'2014-02-01' AS Date), 50, 2)
INSERT [dbo].[Courses] ([Id], [SubjectId], [TeacherId], [StartDate], [Hours], [GroupId]) VALUES (5, 4, 1, CAST(N'2014-02-01' AS Date), 100, 3)
INSERT [dbo].[Courses] ([Id], [SubjectId], [TeacherId], [StartDate], [Hours], [GroupId]) VALUES (6, 3, 1, CAST(N'2014-02-01' AS Date), 50, 3)
SET IDENTITY_INSERT [dbo].[Courses] OFF
SET IDENTITY_INSERT [dbo].[Departments] ON 

INSERT [dbo].[Departments] ([Id], [Name]) VALUES (1, N'Программирования')
INSERT [dbo].[Departments] ([Id], [Name]) VALUES (2, N'Дизайн')
INSERT [dbo].[Departments] ([Id], [Name]) VALUES (3, N'Администрирование')
SET IDENTITY_INSERT [dbo].[Departments] OFF
SET IDENTITY_INSERT [dbo].[ExaminationRolls] ON 

INSERT [dbo].[ExaminationRolls] ([Id], [ExamDate], [TeacherId], [CourseId]) VALUES (11, CAST(N'2015-06-19' AS Date), 3, 3)
INSERT [dbo].[ExaminationRolls] ([Id], [ExamDate], [TeacherId], [CourseId]) VALUES (12, CAST(N'2015-06-19' AS Date), 2, 4)
INSERT [dbo].[ExaminationRolls] ([Id], [ExamDate], [TeacherId], [CourseId]) VALUES (14, CAST(N'2015-06-19' AS Date), 1, 5)
INSERT [dbo].[ExaminationRolls] ([Id], [ExamDate], [TeacherId], [CourseId]) VALUES (15, CAST(N'2015-06-19' AS Date), 1, 6)
SET IDENTITY_INSERT [dbo].[ExaminationRolls] OFF
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (11, 1, 9)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (11, 2, 5)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (11, 3, 4)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (12, 4, 2)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (12, 5, 7)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (14, 1, 10)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (14, 2, 3)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (14, 3, 0)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (15, 1, 2)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (15, 2, 8)
INSERT [dbo].[ExaminationRollsLines] ([ExaminationRollID], [StudentId], [Mark]) VALUES (15, 3, 8)
SET IDENTITY_INSERT [dbo].[Groups] ON 

INSERT [dbo].[Groups] ([Id], [Name], [FormId]) VALUES (2, N'ВПУ 1321', 2)
INSERT [dbo].[Groups] ([Id], [Name], [FormId]) VALUES (3, N'ВНУ 1322', 2)
SET IDENTITY_INSERT [dbo].[Groups] OFF
SET IDENTITY_INSERT [dbo].[LearningForms] ON 

INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (5, N'Воскресная школа')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (3, N'Годичные курсы')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (6, N'Индивидуальные курсы')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (7, N'Корпоративные курсы')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (4, N'Малая академия')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (2, N'Полустационар')
INSERT [dbo].[LearningForms] ([Id], [Name]) VALUES (1, N'Стационар')
SET IDENTITY_INSERT [dbo].[LearningForms] OFF
SET IDENTITY_INSERT [dbo].[Lessons] ON 

INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17019, CAST(N'2014-02-01' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17020, CAST(N'2014-02-08' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17021, CAST(N'2014-02-15' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17022, CAST(N'2014-02-22' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17023, CAST(N'2014-03-01' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17024, CAST(N'2014-03-08' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17025, CAST(N'2014-03-15' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17026, CAST(N'2014-03-22' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17027, CAST(N'2014-03-29' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17028, CAST(N'2014-04-05' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17029, CAST(N'2014-04-12' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17030, CAST(N'2014-04-19' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17031, CAST(N'2014-04-26' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17032, CAST(N'2014-05-03' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17033, CAST(N'2014-05-10' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17034, CAST(N'2014-05-17' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17035, CAST(N'2014-05-24' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17036, CAST(N'2014-05-31' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17037, CAST(N'2014-06-07' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17038, CAST(N'2014-06-14' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17039, CAST(N'2014-06-21' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17040, CAST(N'2014-06-28' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17041, CAST(N'2014-07-05' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17042, CAST(N'2014-07-12' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17043, CAST(N'2014-07-19' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17044, CAST(N'2014-07-26' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17045, CAST(N'2014-08-02' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17046, CAST(N'2014-08-09' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17047, CAST(N'2014-08-16' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17048, CAST(N'2014-08-23' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17049, CAST(N'2014-08-30' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17050, CAST(N'2014-09-06' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17051, CAST(N'2014-09-13' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17052, CAST(N'2014-09-20' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17053, CAST(N'2014-09-27' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17054, CAST(N'2014-10-04' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17055, CAST(N'2014-10-11' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17056, CAST(N'2014-10-18' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17057, CAST(N'2014-10-25' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17058, CAST(N'2014-11-01' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17059, CAST(N'2014-11-08' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17060, CAST(N'2014-11-15' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17061, CAST(N'2014-11-22' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17062, CAST(N'2014-11-29' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17063, CAST(N'2014-12-06' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17064, CAST(N'2014-12-13' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17065, CAST(N'2014-12-20' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17066, CAST(N'2014-12-27' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17067, CAST(N'2015-01-03' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17068, CAST(N'2015-01-10' AS Date), 1, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17069, CAST(N'2014-02-01' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17070, CAST(N'2014-02-08' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17071, CAST(N'2014-02-15' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17072, CAST(N'2014-02-22' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17073, CAST(N'2014-03-01' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17074, CAST(N'2014-03-08' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17075, CAST(N'2014-03-15' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17076, CAST(N'2014-03-22' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17077, CAST(N'2014-03-29' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17078, CAST(N'2014-04-05' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17079, CAST(N'2014-04-12' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17080, CAST(N'2014-04-19' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17081, CAST(N'2014-04-26' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17082, CAST(N'2014-05-03' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17083, CAST(N'2014-05-10' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17084, CAST(N'2014-05-17' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17085, CAST(N'2014-05-24' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17086, CAST(N'2014-05-31' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17087, CAST(N'2014-06-07' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17088, CAST(N'2014-06-14' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17089, CAST(N'2014-06-21' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17090, CAST(N'2014-06-28' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17091, CAST(N'2014-07-05' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17092, CAST(N'2014-07-12' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17093, CAST(N'2014-07-19' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17094, CAST(N'2014-07-26' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17095, CAST(N'2014-08-02' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17096, CAST(N'2014-08-09' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17097, CAST(N'2014-08-16' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17098, CAST(N'2014-08-23' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17099, CAST(N'2014-08-30' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17100, CAST(N'2014-09-06' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17101, CAST(N'2014-09-13' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17102, CAST(N'2014-09-20' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17103, CAST(N'2014-09-27' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17104, CAST(N'2014-10-04' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17105, CAST(N'2014-10-11' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17106, CAST(N'2014-10-18' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17107, CAST(N'2014-10-25' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17108, CAST(N'2014-11-01' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17109, CAST(N'2014-11-08' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17110, CAST(N'2014-11-15' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17111, CAST(N'2014-11-22' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17112, CAST(N'2014-11-29' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17113, CAST(N'2014-12-06' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17114, CAST(N'2014-12-13' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17115, CAST(N'2014-12-20' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17116, CAST(N'2014-12-27' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17117, CAST(N'2015-01-03' AS Date), 2, 1, 3)
GO
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17118, CAST(N'2015-01-10' AS Date), 2, 1, 3)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17119, CAST(N'2014-02-01' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17120, CAST(N'2014-02-08' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17121, CAST(N'2014-02-15' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17122, CAST(N'2014-02-22' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17123, CAST(N'2014-03-01' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17124, CAST(N'2014-03-08' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17125, CAST(N'2014-03-15' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17126, CAST(N'2014-03-22' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17127, CAST(N'2014-03-29' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17128, CAST(N'2014-04-05' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17129, CAST(N'2014-04-12' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17130, CAST(N'2014-04-19' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17131, CAST(N'2014-04-26' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17132, CAST(N'2014-05-03' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17133, CAST(N'2014-05-10' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17134, CAST(N'2014-05-17' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17135, CAST(N'2014-05-24' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17136, CAST(N'2014-05-31' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17137, CAST(N'2014-06-07' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17138, CAST(N'2014-06-14' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17139, CAST(N'2014-06-21' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17140, CAST(N'2014-06-28' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17141, CAST(N'2014-07-05' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17142, CAST(N'2014-07-12' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17143, CAST(N'2014-07-19' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17144, CAST(N'2014-07-26' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17145, CAST(N'2014-08-02' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17146, CAST(N'2014-08-09' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17147, CAST(N'2014-08-16' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17148, CAST(N'2014-08-23' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17149, CAST(N'2014-08-30' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17150, CAST(N'2014-09-06' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17151, CAST(N'2014-09-13' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17152, CAST(N'2014-09-20' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17153, CAST(N'2014-09-27' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17154, CAST(N'2014-10-04' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17155, CAST(N'2014-10-11' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17156, CAST(N'2014-10-18' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17157, CAST(N'2014-10-25' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17158, CAST(N'2014-11-01' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17159, CAST(N'2014-11-08' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17160, CAST(N'2014-11-15' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17161, CAST(N'2014-11-22' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17162, CAST(N'2014-11-29' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17163, CAST(N'2014-12-06' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17164, CAST(N'2014-12-13' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17165, CAST(N'2014-12-20' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17166, CAST(N'2014-12-27' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17167, CAST(N'2015-01-03' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17168, CAST(N'2015-01-10' AS Date), 3, 1, 5)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17169, CAST(N'2014-02-01' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17170, CAST(N'2014-02-08' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17171, CAST(N'2014-02-15' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17172, CAST(N'2014-02-22' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17173, CAST(N'2014-03-01' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17174, CAST(N'2014-03-08' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17175, CAST(N'2014-03-15' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17176, CAST(N'2014-03-22' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17177, CAST(N'2014-03-29' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17178, CAST(N'2014-04-05' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17179, CAST(N'2014-04-12' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17180, CAST(N'2014-04-19' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17181, CAST(N'2014-04-26' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17182, CAST(N'2014-05-03' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17183, CAST(N'2014-05-10' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17184, CAST(N'2014-05-17' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17185, CAST(N'2014-05-24' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17186, CAST(N'2014-05-31' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17187, CAST(N'2014-06-07' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17188, CAST(N'2014-06-14' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17189, CAST(N'2014-06-21' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17190, CAST(N'2014-06-28' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17191, CAST(N'2014-07-05' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17192, CAST(N'2014-07-12' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17193, CAST(N'2014-07-19' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17194, CAST(N'2014-07-26' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17195, CAST(N'2014-08-02' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17196, CAST(N'2014-08-09' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17197, CAST(N'2014-08-16' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17198, CAST(N'2014-08-23' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17199, CAST(N'2014-08-30' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17200, CAST(N'2014-09-06' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17201, CAST(N'2014-09-13' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17202, CAST(N'2014-09-20' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17203, CAST(N'2014-09-27' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17204, CAST(N'2014-10-04' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17205, CAST(N'2014-10-11' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17206, CAST(N'2014-10-18' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17207, CAST(N'2014-10-25' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17208, CAST(N'2014-11-01' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17209, CAST(N'2014-11-08' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17210, CAST(N'2014-11-15' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17211, CAST(N'2014-11-22' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17212, CAST(N'2014-11-29' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17213, CAST(N'2014-12-06' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17214, CAST(N'2014-12-13' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17215, CAST(N'2014-12-20' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17216, CAST(N'2014-12-27' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17217, CAST(N'2015-01-03' AS Date), 1, 2, 4)
GO
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17218, CAST(N'2015-01-10' AS Date), 1, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17219, CAST(N'2014-02-01' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17220, CAST(N'2014-02-08' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17221, CAST(N'2014-02-15' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17222, CAST(N'2014-02-22' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17223, CAST(N'2014-03-01' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17224, CAST(N'2014-03-08' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17225, CAST(N'2014-03-15' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17226, CAST(N'2014-03-22' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17227, CAST(N'2014-03-29' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17228, CAST(N'2014-04-05' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17229, CAST(N'2014-04-12' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17230, CAST(N'2014-04-19' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17231, CAST(N'2014-04-26' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17232, CAST(N'2014-05-03' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17233, CAST(N'2014-05-10' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17234, CAST(N'2014-05-17' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17235, CAST(N'2014-05-24' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17236, CAST(N'2014-05-31' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17237, CAST(N'2014-06-07' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17238, CAST(N'2014-06-14' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17239, CAST(N'2014-06-21' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17240, CAST(N'2014-06-28' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17241, CAST(N'2014-07-05' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17242, CAST(N'2014-07-12' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17243, CAST(N'2014-07-19' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17244, CAST(N'2014-07-26' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17245, CAST(N'2014-08-02' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17246, CAST(N'2014-08-09' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17247, CAST(N'2014-08-16' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17248, CAST(N'2014-08-23' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17249, CAST(N'2014-08-30' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17250, CAST(N'2014-09-06' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17251, CAST(N'2014-09-13' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17252, CAST(N'2014-09-20' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17253, CAST(N'2014-09-27' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17254, CAST(N'2014-10-04' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17255, CAST(N'2014-10-11' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17256, CAST(N'2014-10-18' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17257, CAST(N'2014-10-25' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17258, CAST(N'2014-11-01' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17259, CAST(N'2014-11-08' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17260, CAST(N'2014-11-15' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17261, CAST(N'2014-11-22' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17262, CAST(N'2014-11-29' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17263, CAST(N'2014-12-06' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17264, CAST(N'2014-12-13' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17265, CAST(N'2014-12-20' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17266, CAST(N'2014-12-27' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17267, CAST(N'2015-01-03' AS Date), 2, 2, 4)
INSERT [dbo].[Lessons] ([Id], [ExecutionDate], [PairNumber], [RoomId], [CourseId]) VALUES (17268, CAST(N'2015-01-10' AS Date), 2, 2, 4)
SET IDENTITY_INSERT [dbo].[Lessons] OFF
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17019, 1, 1, 11, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17019, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17019, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17020, 1, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17020, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17020, 3, 1, 1, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17021, 1, 1, 10, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17021, 2, 1, 7, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17021, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17022, 1, 1, 4, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17022, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17022, 3, 1, 3, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17023, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17023, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17023, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17024, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17024, 2, 1, 7, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17024, 3, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17025, 1, 1, 7, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17025, 2, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17025, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17026, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17026, 2, 1, 10, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17026, 3, 1, 4, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17027, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17027, 2, 1, 1, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17027, 3, 1, 9, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17028, 1, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17028, 2, 1, 6, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17028, 3, 1, 8, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17029, 1, 1, 3, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17029, 2, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17029, 3, 1, 3, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17030, 1, 1, 0, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17030, 2, 1, 8, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17030, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17031, 1, 1, 1, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17031, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17031, 3, 1, 1, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17032, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17032, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17032, 3, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17033, 1, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17033, 2, 1, 7, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17033, 3, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17034, 1, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17034, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17034, 3, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17035, 1, 1, 3, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17035, 2, 1, 1, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17035, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17036, 1, 1, 5, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17036, 2, 1, 0, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17036, 3, 1, 7, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17037, 1, 1, 8, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17037, 2, 1, 0, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17037, 3, 1, 6, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17038, 1, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17038, 2, 1, 9, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17038, 3, 1, 3, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17039, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17039, 2, 1, 1, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17039, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17040, 1, 1, 8, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17040, 2, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17040, 3, 1, 5, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17041, 1, 1, 4, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17041, 2, 1, 9, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17041, 3, 1, 0, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17042, 1, 1, 1, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17042, 2, 1, 2, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17042, 3, 1, 6, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17043, 1, 1, 9, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17043, 2, 1, 9, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17043, 3, 1, 0, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17044, 1, 1, 2, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17044, 2, 1, 5, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17044, 3, 1, 4, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17045, 1, 1, 3, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17045, 2, 1, 4, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17045, 3, 1, 2, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17046, 1, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17046, 2, 1, 2, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17046, 3, 1, 11, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17047, 1, 1, 10, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17047, 2, 1, 9, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17047, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17048, 1, 1, 3, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17048, 2, 1, 0, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17048, 3, 1, 10, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17049, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17049, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17049, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17050, 1, 1, 9, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17050, 2, 1, 11, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17050, 3, 1, 3, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17051, 1, 1, 7, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17051, 2, 1, 5, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17051, 3, 1, 10, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17052, 1, 1, 2, 1, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17052, 2, 1, 8, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17052, 3, 1, 6, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17053, 1, 1, 0, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17053, 2, 1, 2, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17053, 3, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17054, 1, 1, 11, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17054, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17054, 3, 1, 2, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17055, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17055, 2, 1, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17055, 3, 1, 10, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17056, 1, 1, 5, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17056, 2, 1, 10, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17056, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17057, 1, 1, 2, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17057, 2, 1, 5, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17057, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17058, 1, 1, 2, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17058, 2, 1, 7, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17058, 3, 1, 4, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17059, 1, 1, 3, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17059, 2, 1, 10, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17059, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17060, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17060, 2, 1, 6, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17060, 3, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17061, 1, 1, 7, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17061, 2, 1, 10, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17061, 3, 1, 8, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17062, 1, 1, 11, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17062, 2, 1, 6, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17062, 3, 1, 7, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17063, 1, 1, 1, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17063, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17063, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17064, 1, 1, 5, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17064, 2, 1, 4, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17064, 3, 1, 11, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17065, 1, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17065, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17065, 3, 1, 0, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17066, 1, 1, 7, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17066, 2, 1, 10, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17066, 3, 1, 4, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17067, 1, 1, 10, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17067, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17067, 3, 1, 5, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17068, 1, 1, 6, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17068, 2, 1, 6, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17068, 3, 1, 1, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17069, 1, 1, 4, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17069, 2, 1, 4, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17069, 3, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17070, 1, 1, 2, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17070, 2, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17070, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17071, 1, 1, 2, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17071, 2, 1, 0, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17071, 3, 1, 3, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17072, 1, 1, 7, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17072, 2, 1, 11, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17072, 3, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17073, 1, 1, 4, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17073, 2, 1, 4, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17073, 3, 1, 2, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17074, 1, 1, 3, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17074, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17074, 3, 1, 8, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17075, 1, 1, 6, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17075, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17075, 3, 1, 8, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17076, 1, 1, 5, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17076, 2, 1, 8, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17076, 3, 1, 10, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17077, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17077, 2, 1, 3, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17077, 3, 1, 3, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17078, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17078, 2, 1, 8, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17078, 3, 1, 5, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17079, 1, 1, 7, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17079, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17079, 3, 1, 7, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17080, 1, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17080, 2, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17080, 3, 1, 0, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17081, 1, 1, 4, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17081, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17081, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17082, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17082, 2, 1, 7, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17082, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17083, 1, 1, 10, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17083, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17083, 3, 1, 9, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17084, 1, 1, 2, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17084, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17084, 3, 1, 2, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17085, 1, 1, 6, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17085, 2, 0, 0, 0, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17085, 3, 1, 6, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17086, 1, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17086, 2, 1, 6, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17086, 3, 1, 9, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17087, 1, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17087, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17087, 3, 1, 5, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17088, 1, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17088, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17088, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17089, 1, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17089, 2, 1, 8, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17089, 3, 1, 9, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17090, 1, 1, 4, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17090, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17090, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17091, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17091, 2, 1, 1, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17091, 3, 1, 5, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17092, 1, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17092, 2, 1, 9, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17092, 3, 1, 8, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17093, 1, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17093, 2, 1, 8, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17093, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17094, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17094, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17094, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17095, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17095, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17095, 3, 1, 7, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17096, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17096, 2, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17096, 3, 1, 11, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17097, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17097, 2, 1, 10, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17097, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17098, 1, 1, 9, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17098, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17098, 3, 1, 4, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17099, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17099, 2, 1, 8, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17099, 3, 1, 8, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17100, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17100, 2, 1, 3, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17100, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17101, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17101, 2, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17101, 3, 1, 8, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17102, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17102, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17102, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17103, 1, 1, 9, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17103, 2, 1, 6, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17103, 3, 1, 1, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17104, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17104, 2, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17104, 3, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17105, 1, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17105, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17105, 3, 1, 8, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17106, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17106, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17106, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17107, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17107, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17107, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17108, 1, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17108, 2, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17108, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17109, 1, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17109, 2, 1, 9, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17109, 3, 1, 3, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17110, 1, 1, 8, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17110, 2, 1, 9, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17110, 3, 1, 8, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17111, 1, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17111, 2, 1, 11, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17111, 3, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17112, 1, 1, 10, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17112, 2, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17112, 3, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17113, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17113, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17113, 3, 1, 11, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17114, 1, 1, 10, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17114, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17114, 3, 1, 9, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17115, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17115, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17115, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17116, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17116, 2, 1, 4, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17116, 3, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17117, 1, 1, 11, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17117, 2, 1, 1, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17117, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17118, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17118, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17118, 3, 0, 0, 0, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17119, 1, 1, 0, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17119, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17119, 3, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17120, 1, 1, 6, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17120, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17120, 3, 1, 8, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17121, 1, 1, 3, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17121, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17121, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17122, 1, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17122, 2, 1, 5, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17122, 3, 1, 9, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17123, 1, 1, 2, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17123, 2, 1, 1, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17123, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17124, 1, 1, 9, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17124, 2, 1, 5, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17124, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17125, 1, 1, 9, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17125, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17125, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17126, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17126, 2, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17126, 3, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17127, 1, 1, 3, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17127, 2, 1, 3, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17127, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17128, 1, 1, 5, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17128, 2, 1, 1, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17128, 3, 1, 7, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17129, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17129, 2, 1, 0, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17129, 3, 1, 9, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17130, 1, 1, 5, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17130, 2, 1, 1, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17130, 3, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17131, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17131, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17131, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17132, 1, 1, 8, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17132, 2, 1, 8, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17132, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17133, 1, 1, 8, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17133, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17133, 3, 1, 2, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17134, 1, 1, 9, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17134, 2, 1, 9, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17134, 3, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17135, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17135, 2, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17135, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17136, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17136, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17136, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17137, 1, 1, 5, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17137, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17137, 3, 1, 9, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17138, 1, 1, 10, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17138, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17138, 3, 1, 1, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17139, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17139, 2, 1, 5, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17139, 3, 1, 11, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17140, 1, 1, 5, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17140, 2, 1, 9, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17140, 3, 1, 3, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17141, 1, 1, 8, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17141, 2, 1, 9, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17141, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17142, 1, 1, 11, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17142, 2, 1, 11, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17142, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17143, 1, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17143, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17143, 3, 1, 0, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17144, 1, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17144, 2, 1, 4, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17144, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17145, 1, 1, 10, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17145, 2, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17145, 3, 1, 10, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17146, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17146, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17146, 3, 1, 5, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17147, 1, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17147, 2, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17147, 3, 1, 8, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17148, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17148, 2, 1, 7, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17148, 3, 1, 8, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17149, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17149, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17149, 3, 1, 2, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17150, 1, 1, 2, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17150, 2, 1, 2, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17150, 3, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17151, 1, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17151, 2, 1, 8, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17151, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17152, 1, 1, 1, 3, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17152, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17152, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17153, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17153, 2, 1, 11, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17153, 3, 1, 9, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17154, 1, 1, 11, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17154, 2, 1, 8, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17154, 3, 1, 0, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17155, 1, 1, 2, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17155, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17155, 3, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17156, 1, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17156, 2, 1, 2, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17156, 3, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17157, 1, 1, 8, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17157, 2, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17157, 3, 1, 5, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17158, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17158, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17158, 3, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17159, 1, 1, 3, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17159, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17159, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17160, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17160, 2, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17160, 3, 1, 1, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17161, 1, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17161, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17161, 3, 1, 2, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17162, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17162, 2, 1, 10, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17162, 3, 1, 1, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17163, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17163, 2, 1, 4, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17163, 3, 1, 2, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17164, 1, 1, 8, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17164, 2, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17164, 3, 1, 5, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17165, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17165, 2, 1, 10, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17165, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17166, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17166, 2, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17166, 3, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17167, 1, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17167, 2, 1, 10, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17167, 3, 1, 8, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17168, 1, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17168, 2, 1, 7, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17168, 3, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17169, 4, 1, 9, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17169, 5, 1, 3, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17170, 4, 1, 3, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17170, 5, 1, 3, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17171, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17171, 5, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17172, 4, 1, 9, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17172, 5, 1, 9, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17173, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17173, 5, 1, 5, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17174, 4, 1, 9, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17174, 5, 1, 1, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17175, 4, 1, 10, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17175, 5, 1, 11, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17176, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17176, 5, 1, 0, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17177, 4, 1, 9, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17177, 5, 1, 8, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17178, 4, 1, 1, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17178, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17179, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17179, 5, 1, 1, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17180, 4, 1, 9, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17180, 5, 1, 3, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17181, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17181, 5, 1, 1, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17182, 4, 1, 0, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17182, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17183, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17183, 5, 1, 6, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17184, 4, 1, 1, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17184, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17185, 4, 1, 1, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17185, 5, 1, 1, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17186, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17186, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17187, 4, 1, 7, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17187, 5, 1, 7, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17188, 4, 1, 2, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17188, 5, 1, 8, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17189, 4, 1, 11, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17189, 5, 1, 0, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17190, 4, 1, 2, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17190, 5, 1, 8, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17191, 4, 1, 7, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17191, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17192, 4, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17192, 5, 1, 11, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17193, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17193, 5, 1, 0, 10, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17194, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17194, 5, 1, 0, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17195, 4, 1, 3, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17195, 5, 1, 1, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17196, 4, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17196, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17197, 4, 1, 1, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17197, 5, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17198, 4, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17198, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17199, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17199, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17200, 4, 1, 11, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17200, 5, 1, 1, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17201, 4, 1, 0, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17201, 5, 1, 11, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17202, 4, 1, 9, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17202, 5, 1, 6, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17203, 4, 1, 4, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17203, 5, 1, 11, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17204, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17204, 5, 1, 5, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17205, 4, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17205, 5, 1, 8, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17206, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17206, 5, 1, 2, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17207, 4, 1, 6, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17207, 5, 1, 2, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17208, 4, 1, 7, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17208, 5, 1, 11, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17209, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17209, 5, 1, 9, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17210, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17210, 5, 1, 4, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17211, 4, 1, 10, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17211, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17212, 4, 1, 8, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17212, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17213, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17213, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17214, 4, 1, 6, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17214, 5, 1, 11, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17215, 4, 1, 5, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17215, 5, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17216, 4, 1, 5, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17216, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17217, 4, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17217, 5, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17218, 4, 1, 6, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17218, 5, 1, 2, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17219, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17219, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17220, 4, 1, 0, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17220, 5, 1, 11, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17221, 4, 1, 4, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17221, 5, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17222, 4, 1, 10, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17222, 5, 1, 5, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17223, 4, 1, 11, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17223, 5, 1, 10, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17224, 4, 1, 7, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17224, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17225, 4, 1, 9, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17225, 5, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17226, 4, 1, 3, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17226, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17227, 4, 1, 1, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17227, 5, 1, 10, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17228, 4, 1, 10, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17228, 5, 1, 2, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17229, 4, 1, 4, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17229, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17230, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17230, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17231, 4, 1, 8, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17231, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17232, 4, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17232, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17233, 4, 1, 2, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17233, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17234, 4, 1, 8, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17234, 5, 1, 10, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17235, 4, 1, 8, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17235, 5, 1, 9, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17236, 4, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17236, 5, 1, 2, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17237, 4, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17237, 5, 1, 0, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17238, 4, 1, 4, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17238, 5, 1, 3, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17239, 4, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17239, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17240, 4, 1, 4, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17240, 5, 1, 0, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17241, 4, 1, 9, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17241, 5, 1, 3, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17242, 4, 1, 8, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17242, 5, 1, 7, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17243, 4, 1, 0, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17243, 5, 1, 4, 4, N'')
GO
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17244, 4, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17244, 5, 1, 11, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17245, 4, 1, 4, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17245, 5, 1, 3, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17246, 4, 1, 2, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17246, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17247, 4, 1, 3, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17247, 5, 1, 4, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17248, 4, 1, 7, 4, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17248, 5, 1, 2, 2, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17249, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17249, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17250, 4, 1, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17250, 5, 1, 7, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17251, 4, 1, 10, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17251, 5, 1, 8, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17252, 4, 1, 9, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17252, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17253, 4, 1, 4, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17253, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17254, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17254, 5, 1, 4, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17255, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17255, 5, 1, 3, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17256, 4, 1, 11, 8, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17256, 5, 1, 8, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17257, 4, 1, 11, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17257, 5, 1, 1, 10, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17258, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17258, 5, 1, 10, 11, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17259, 4, 1, 1, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17259, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17260, 4, 1, 11, 6, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17260, 5, 1, 11, 7, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17261, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17261, 5, 1, 2, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17262, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17262, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17263, 4, 1, 10, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17263, 5, 1, 5, 1, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17264, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17264, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17265, 4, 1, 4, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17265, 5, 1, 0, 5, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17266, 4, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17266, 5, 1, 1, 3, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17267, 4, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17267, 5, 0, 0, 0, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17268, 4, 1, 7, 9, N'')
INSERT [dbo].[LessonsDetails] ([LessonId], [StudentId], [StudentPresence], [ClassMark], [HomeMark], [Note]) VALUES (17268, 5, 1, 5, 4, N'')
INSERT [dbo].[Notes] ([Id], [Note]) VALUES (1, N'56456')
SET IDENTITY_INSERT [dbo].[Persons] ON 

INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (1, N'Torvalds', N'Linus', NULL, CAST(N'1970-01-01' AS Date), 1, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (2, N'Kohen', N'Bram', NULL, CAST(N'1970-01-01' AS Date), 2, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (3, N'Kharmak', N'John', N'D.', CAST(N'1970-01-01' AS Date), 1, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (4, N'Brin', N'Sergey', NULL, CAST(N'1970-01-01' AS Date), 2, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (5, N'Page', N'Larry', NULL, CAST(N'1970-01-01' AS Date), 1, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (17, N'Knuth', N'Donald', NULL, CAST(N'1950-01-01' AS Date), 1, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (18, N'Thompson', N'Ken', NULL, CAST(N'1950-01-01' AS Date), 2, NULL, NULL)
INSERT [dbo].[Persons] ([Id], [LastName], [FirstName], [Patronymic], [BirthDay], [AddressId], [PhotoId], [NoteId]) VALUES (19, N'Stroustrup', N'Bjarne', NULL, CAST(N'1950-01-01' AS Date), 1, NULL, NULL)
SET IDENTITY_INSERT [dbo].[Persons] OFF
SET IDENTITY_INSERT [dbo].[PhoneNumbers] ON 

INSERT [dbo].[PhoneNumbers] ([Id], [PhoneNumber], [PersonId]) VALUES (1, N'11111', 1)
INSERT [dbo].[PhoneNumbers] ([Id], [PhoneNumber], [PersonId]) VALUES (2, N'22222', 2)
INSERT [dbo].[PhoneNumbers] ([Id], [PhoneNumber], [PersonId]) VALUES (3, N'33333', 3)
INSERT [dbo].[PhoneNumbers] ([Id], [PhoneNumber], [PersonId]) VALUES (4, N'44444', 1)
INSERT [dbo].[PhoneNumbers] ([Id], [PhoneNumber], [PersonId]) VALUES (5, N'44444', 2)
SET IDENTITY_INSERT [dbo].[PhoneNumbers] OFF
SET IDENTITY_INSERT [dbo].[Rooms] ON 

INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (1, N'101', 3, 10, 0, 1, NULL)
INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (2, N'201', 2, 10, 0, 1, NULL)
INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (3, N'202', 3, 15, 0, 1, NULL)
INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (4, N'203', 1, 10, 0, 1, NULL)
INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (5, N'204', 2, 15, 0, 0, NULL)
INSERT [dbo].[Rooms] ([Id], [Number], [RoomsTypeId], [ComputersNumber], [ConferenceHall], [IsEducational], [Note]) VALUES (6, N'205', 3, 0, 1, 0, NULL)
SET IDENTITY_INSERT [dbo].[Rooms] OFF
SET IDENTITY_INSERT [dbo].[RoomsType] ON 

INSERT [dbo].[RoomsType] ([Id], [Name]) VALUES (2, N'For Admins')
INSERT [dbo].[RoomsType] ([Id], [Name]) VALUES (1, N'For Designers')
INSERT [dbo].[RoomsType] ([Id], [Name]) VALUES (4, N'For Managers')
INSERT [dbo].[RoomsType] ([Id], [Name]) VALUES (3, N'For Programmers')
SET IDENTITY_INSERT [dbo].[RoomsType] OFF
SET IDENTITY_INSERT [dbo].[Seasons] ON 

INSERT [dbo].[Seasons] ([Id], [Name]) VALUES (1, N'Spring    ')
INSERT [dbo].[Seasons] ([Id], [Name]) VALUES (2, N'Autumn    ')
SET IDENTITY_INSERT [dbo].[Seasons] OFF
SET IDENTITY_INSERT [dbo].[Specializations] ON 

INSERT [dbo].[Specializations] ([Id], [Name]) VALUES (4, N'Administration')
INSERT [dbo].[Specializations] ([Id], [Name]) VALUES (1, N'Base')
INSERT [dbo].[Specializations] ([Id], [Name]) VALUES (3, N'Design')
INSERT [dbo].[Specializations] ([Id], [Name]) VALUES (2, N'Programming')
SET IDENTITY_INSERT [dbo].[Specializations] OFF
SET IDENTITY_INSERT [dbo].[Streams] ON 

INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (1, N'2012', 1)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (2, N'2012', 2)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (3, N'2013', 1)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (4, N'2013', 2)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (5, N'2014', 1)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (6, N'2014', 2)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (7, N'2015', 1)
INSERT [dbo].[Streams] ([Id], [Year], [SeasonId]) VALUES (8, N'2015', 2)
SET IDENTITY_INSERT [dbo].[Streams] OFF
SET IDENTITY_INSERT [dbo].[Students] ON 

INSERT [dbo].[Students] ([Id], [PersonId], [GroupId], [StreamId], [SpecializationId]) VALUES (1, 1, 3, 1, 2)
INSERT [dbo].[Students] ([Id], [PersonId], [GroupId], [StreamId], [SpecializationId]) VALUES (2, 2, 3, 1, 2)
INSERT [dbo].[Students] ([Id], [PersonId], [GroupId], [StreamId], [SpecializationId]) VALUES (3, 3, 3, 1, 2)
INSERT [dbo].[Students] ([Id], [PersonId], [GroupId], [StreamId], [SpecializationId]) VALUES (4, 4, 2, 2, 1)
INSERT [dbo].[Students] ([Id], [PersonId], [GroupId], [StreamId], [SpecializationId]) VALUES (5, 5, 2, 2, 1)
SET IDENTITY_INSERT [dbo].[Students] OFF
SET IDENTITY_INSERT [dbo].[Subjects] ON 

INSERT [dbo].[Subjects] ([Id], [Name], [DepartmentId]) VALUES (1, N'C++', 1)
INSERT [dbo].[Subjects] ([Id], [Name], [DepartmentId]) VALUES (2, N'C#', 1)
INSERT [dbo].[Subjects] ([Id], [Name], [DepartmentId]) VALUES (3, N'JavaScript', 1)
INSERT [dbo].[Subjects] ([Id], [Name], [DepartmentId]) VALUES (4, N'SQL Server', 1)
SET IDENTITY_INSERT [dbo].[Subjects] OFF
SET IDENTITY_INSERT [dbo].[Teachers] ON 

INSERT [dbo].[Teachers] ([Id], [PersonId], [DepartmentId]) VALUES (1, 17, 1)
INSERT [dbo].[Teachers] ([Id], [PersonId], [DepartmentId]) VALUES (2, 18, 1)
INSERT [dbo].[Teachers] ([Id], [PersonId], [DepartmentId]) VALUES (3, 19, 1)
SET IDENTITY_INSERT [dbo].[Teachers] OFF
INSERT [dbo].[Users] ([Id], [Login], [Password]) VALUES (1, N'11111', N'111111111')
INSERT [dbo].[Users] ([Id], [Login], [Password]) VALUES (3, N'sdfad', N'sdfsadfasdfadf')
/****** Object:  Index [uq_courses]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Courses] ADD  CONSTRAINT [uq_courses] UNIQUE NONCLUSTERED 
(
	[SubjectId] ASC,
	[GroupId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [uq_examinationrolls]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[ExaminationRolls] ADD  CONSTRAINT [uq_examinationrolls] UNIQUE NONCLUSTERED 
(
	[ExamDate] ASC,
	[CourseId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [uq_examinationRollLines]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[ExaminationRollsLines] ADD  CONSTRAINT [uq_examinationRollLines] UNIQUE NONCLUSTERED 
(
	[ExaminationRollID] ASC,
	[StudentId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [UQ__Groups__737584F6523EE2E8]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Groups] ADD UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [UQ__Learning__737584F60FC03377]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[LearningForms] ADD UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [uq_Lessons]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Lessons] ADD  CONSTRAINT [uq_Lessons] UNIQUE NONCLUSTERED 
(
	[ExecutionDate] ASC,
	[PairNumber] ASC,
	[RoomId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [uq_LessonsDetails]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[LessonsDetails] ADD  CONSTRAINT [uq_LessonsDetails] UNIQUE NONCLUSTERED 
(
	[LessonId] ASC,
	[StudentId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [uq_rooms]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Rooms] ADD  CONSTRAINT [uq_rooms] UNIQUE NONCLUSTERED 
(
	[Number] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [uq_roomsTypes]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[RoomsType] ADD  CONSTRAINT [uq_roomsTypes] UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [UQ__Speciali__737584F6F11772A1]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Specializations] ADD UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [uq_subjects]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Subjects] ADD  CONSTRAINT [uq_subjects] UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON

GO
/****** Object:  Index [UQ__Logins__5E55825B002A716F]    Script Date: 19.06.2015 16:46:23 ******/
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [UQ__Logins__5E55825B002A716F] UNIQUE NONCLUSTERED 
(
	[Login] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Courses]  WITH CHECK ADD  CONSTRAINT [FK__Course__SubjectI__22751F6C] FOREIGN KEY([SubjectId])
REFERENCES [dbo].[Subjects] ([Id])
GO
ALTER TABLE [dbo].[Courses] CHECK CONSTRAINT [FK__Course__SubjectI__22751F6C]
GO
ALTER TABLE [dbo].[Courses]  WITH CHECK ADD  CONSTRAINT [FK__Course__TeacherI__236943A5] FOREIGN KEY([TeacherId])
REFERENCES [dbo].[Teachers] ([Id])
GO
ALTER TABLE [dbo].[Courses] CHECK CONSTRAINT [FK__Course__TeacherI__236943A5]
GO
ALTER TABLE [dbo].[Courses]  WITH CHECK ADD  CONSTRAINT [FK_Courses_Groups] FOREIGN KEY([GroupId])
REFERENCES [dbo].[Groups] ([Id])
GO
ALTER TABLE [dbo].[Courses] CHECK CONSTRAINT [FK_Courses_Groups]
GO
ALTER TABLE [dbo].[ExaminationRolls]  WITH CHECK ADD  CONSTRAINT [FK__Examinati__Subje__18EBB532] FOREIGN KEY([CourseId])
REFERENCES [dbo].[Courses] ([Id])
GO
ALTER TABLE [dbo].[ExaminationRolls] CHECK CONSTRAINT [FK__Examinati__Subje__18EBB532]
GO
ALTER TABLE [dbo].[ExaminationRolls]  WITH CHECK ADD  CONSTRAINT [FK__Examinati__Teach__17F790F9] FOREIGN KEY([TeacherId])
REFERENCES [dbo].[Teachers] ([Id])
GO
ALTER TABLE [dbo].[ExaminationRolls] CHECK CONSTRAINT [FK__Examinati__Teach__17F790F9]
GO
ALTER TABLE [dbo].[ExaminationRollsLines]  WITH CHECK ADD  CONSTRAINT [FK__Examinati__Exami__1AD3FDA4] FOREIGN KEY([ExaminationRollID])
REFERENCES [dbo].[ExaminationRolls] ([Id])
GO
ALTER TABLE [dbo].[ExaminationRollsLines] CHECK CONSTRAINT [FK__Examinati__Exami__1AD3FDA4]
GO
ALTER TABLE [dbo].[ExaminationRollsLines]  WITH CHECK ADD  CONSTRAINT [FK__Examinati__Stude__1BC821DD] FOREIGN KEY([StudentId])
REFERENCES [dbo].[Students] ([Id])
GO
ALTER TABLE [dbo].[ExaminationRollsLines] CHECK CONSTRAINT [FK__Examinati__Stude__1BC821DD]
GO
ALTER TABLE [dbo].[Groups]  WITH CHECK ADD FOREIGN KEY([FormId])
REFERENCES [dbo].[LearningForms] ([Id])
GO
ALTER TABLE [dbo].[Lessons]  WITH CHECK ADD  CONSTRAINT [FK__Lessons__CourseI__37703C52] FOREIGN KEY([CourseId])
REFERENCES [dbo].[Courses] ([Id])
GO
ALTER TABLE [dbo].[Lessons] CHECK CONSTRAINT [FK__Lessons__CourseI__37703C52]
GO
ALTER TABLE [dbo].[Lessons]  WITH CHECK ADD  CONSTRAINT [FK__Lessons__RoomId__3864608B] FOREIGN KEY([RoomId])
REFERENCES [dbo].[Rooms] ([Id])
GO
ALTER TABLE [dbo].[Lessons] CHECK CONSTRAINT [FK__Lessons__RoomId__3864608B]
GO
ALTER TABLE [dbo].[LessonsDetails]  WITH CHECK ADD  CONSTRAINT [FK__LessonsDe__Lesso__3A4CA8FD] FOREIGN KEY([LessonId])
REFERENCES [dbo].[Lessons] ([Id])
GO
ALTER TABLE [dbo].[LessonsDetails] CHECK CONSTRAINT [FK__LessonsDe__Lesso__3A4CA8FD]
GO
ALTER TABLE [dbo].[LessonsDetails]  WITH CHECK ADD FOREIGN KEY([StudentId])
REFERENCES [dbo].[Students] ([Id])
GO
ALTER TABLE [dbo].[Persons]  WITH CHECK ADD  CONSTRAINT [FK_Persons_Addresses] FOREIGN KEY([AddressId])
REFERENCES [dbo].[Addresses] ([Id])
GO
ALTER TABLE [dbo].[Persons] CHECK CONSTRAINT [FK_Persons_Addresses]
GO
ALTER TABLE [dbo].[Persons]  WITH CHECK ADD  CONSTRAINT [FK_Persons_Notes] FOREIGN KEY([NoteId])
REFERENCES [dbo].[Notes] ([Id])
GO
ALTER TABLE [dbo].[Persons] CHECK CONSTRAINT [FK_Persons_Notes]
GO
ALTER TABLE [dbo].[Persons]  WITH CHECK ADD  CONSTRAINT [FK_Persons_Photos] FOREIGN KEY([PhotoId])
REFERENCES [dbo].[Photos] ([Id])
GO
ALTER TABLE [dbo].[Persons] CHECK CONSTRAINT [FK_Persons_Photos]
GO
ALTER TABLE [dbo].[PhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_PhoneNumbers_Persons] FOREIGN KEY([PersonId])
REFERENCES [dbo].[Persons] ([Id])
GO
ALTER TABLE [dbo].[PhoneNumbers] CHECK CONSTRAINT [FK_PhoneNumbers_Persons]
GO
ALTER TABLE [dbo].[Rooms]  WITH CHECK ADD FOREIGN KEY([RoomsTypeId])
REFERENCES [dbo].[RoomsType] ([Id])
GO
ALTER TABLE [dbo].[Streams]  WITH CHECK ADD  CONSTRAINT [FK_Streams_Seasons] FOREIGN KEY([SeasonId])
REFERENCES [dbo].[Seasons] ([Id])
GO
ALTER TABLE [dbo].[Streams] CHECK CONSTRAINT [FK_Streams_Seasons]
GO
ALTER TABLE [dbo].[Students]  WITH CHECK ADD  CONSTRAINT [FK__Student__GroupId__6C190EBB] FOREIGN KEY([GroupId])
REFERENCES [dbo].[Groups] ([Id])
GO
ALTER TABLE [dbo].[Students] CHECK CONSTRAINT [FK__Student__GroupId__6C190EBB]
GO
ALTER TABLE [dbo].[Students]  WITH CHECK ADD  CONSTRAINT [FK__Student__PersonI__6B24EA82] FOREIGN KEY([PersonId])
REFERENCES [dbo].[Persons] ([Id])
GO
ALTER TABLE [dbo].[Students] CHECK CONSTRAINT [FK__Student__PersonI__6B24EA82]
GO
ALTER TABLE [dbo].[Students]  WITH CHECK ADD  CONSTRAINT [FK_Student_Specializations] FOREIGN KEY([SpecializationId])
REFERENCES [dbo].[Specializations] ([Id])
GO
ALTER TABLE [dbo].[Students] CHECK CONSTRAINT [FK_Student_Specializations]
GO
ALTER TABLE [dbo].[Students]  WITH CHECK ADD  CONSTRAINT [FK_Student_Streams] FOREIGN KEY([StreamId])
REFERENCES [dbo].[Streams] ([Id])
GO
ALTER TABLE [dbo].[Students] CHECK CONSTRAINT [FK_Student_Streams]
GO
ALTER TABLE [dbo].[Teachers]  WITH CHECK ADD  CONSTRAINT [FK_Teachers_Departments1] FOREIGN KEY([DepartmentId])
REFERENCES [dbo].[Departments] ([Id])
GO
ALTER TABLE [dbo].[Teachers] CHECK CONSTRAINT [FK_Teachers_Departments1]
GO
ALTER TABLE [dbo].[Teachers]  WITH CHECK ADD  CONSTRAINT [FK_Teachers_Persons1] FOREIGN KEY([PersonId])
REFERENCES [dbo].[Persons] ([Id])
GO
ALTER TABLE [dbo].[Teachers] CHECK CONSTRAINT [FK_Teachers_Persons1]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Persons] FOREIGN KEY([Id])
REFERENCES [dbo].[Persons] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Persons]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [CK__Logins__Login__117F9D94] CHECK  ((len([Login])>(2)))
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [CK__Logins__Login__117F9D94]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [CK__Logins__Password__1273C1CD] CHECK  ((len([Password])>(7)))
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [CK__Logins__Password__1273C1CD]
GO
/****** Object:  StoredProcedure [dbo].[spAttendance]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spAttendance]
AS
select ExecutionDate AS [Date], PairNumber AS Pair, Rooms.Number AS [Room],  
		v_Courses.Subject,		
		 v_Courses.Lastname+' '+v_Courses.FirstName AS [Teacher], v_courses.[Group],
		 v_Students.LastName+' '+v_Students.FirstName AS [Student],
		 StudentPresence AS [Attended], HomeMark, ClassMark, LessonsDetails.Note

from lessons join lessonsDetails ON lessons.Id=lessonsDetails.LessonId  
JOIN Rooms ON Lessons.RoomId=Rooms.Id 
JOIN v_courses ON lessons.CourseId=v_Courses.Id 
JOIN v_students On lessonsDetails.StudentId=v_students.Id
Order BY ExecutionDate, Pair,  [Group], Student


-- exec spAttendance
 
GO
/****** Object:  StoredProcedure [dbo].[spAttendanceByStream]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spAttendanceByStream]
@StreamYear char(4),
@StreamSeason nvarchar(10)
AS
select ExecutionDate AS [Date], PairNumber AS Pair, Rooms.Number AS [Room],  
		v_Courses.Subject,		
		 v_Courses.Lastname+' '+v_Courses.FirstName AS [Teacher], v_courses.[Group],
		 Persons.LastName+' '+Persons.FirstName AS [Student],
		 StudentPresence AS [Attended], HomeMark, ClassMark, LessonsDetails.Note

from lessons join lessonsDetails ON lessons.Id=lessonsDetails.LessonId  
JOIN Rooms ON Lessons.RoomId=Rooms.Id 
JOIN v_courses ON lessons.CourseId=v_Courses.Id 
JOIN Students On lessonsDetails.StudentId=Students.Id
JOIN Persons ON Persons.Id=Students.PersonId
JOIN Streams ON Students.StreamId=Streams.Id 
JOIN Seasons ON Streams.SeasonId=Seasons.Id
WHERE Streams.Year=@StreamYear AND seasons.Name=@StreamSeason
Order BY ExecutionDate, Pair,  [Group], Student
 

--exec spAttendanceByStream 2012, 'autumn'

GO
/****** Object:  StoredProcedure [dbo].[spCreateLesson]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROC [dbo].[spCreateLesson]
@StartDate date,
@PairNumber int,
@RoomId int,
@CourseId int,
@RepeatsNumber int
AS
BEGIN
	Declare @i int=0;

	while(@i<@RepeatsNumber)
	begin
		insert lessons values(DATEADD(day, 7*@i, @StartDate), @PairNumber, @RoomId, @CourseId);
		SET @i=@i+1;
	end
END
GO
/****** Object:  StoredProcedure [dbo].[spCreateRandomExamRoll]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spCreateRandomExamRoll]
@Date date,
@CourseId int,
@TeacherId int=null
AS
BEGIN
	if @TeacherId IS NULL
		select @TeacherId=TeacherId From Courses where id=@CourseId;

	insert ExaminationRolls 
	values(@Date, @TeacherId, @CourseId);

	Declare @Examid int;
	select @examid=id from ExaminationRolls 
	WHERE ExamDate=@Date AND TeacherId=@TeacherId AND CourseId=@CourseId

	insert ExaminationRollsLines
	select @ExamId, Id, CAST(RAND(CHECKSUM(NEWID())) * 12 as tinyint)  from students where GroupId = (Select GroupId From Courses Where Courses.Id=@CourseId)


END

GO
/****** Object:  StoredProcedure [dbo].[spFillLessons]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spFillLessons]
AS
BEGIN
	Declare Lessons_Cursor Cursor
	STATIC
	FOR
		select GroupId, Lessons.Id from Lessons JOIN Courses ON Lessons.CourseId=Courses.Id;

	Declare @GroupId int, @LessonId int
	Open Lessons_Cursor;
	Fetch next FROM Lessons_Cursor into @GroupId, @LessonId;
	While @@Fetch_Status=0
	BEGIN
		Insert into LessonsDetails
		select @LessonId, Students.Id, CAST( round(RAND(CHECKSUM(NEWID()))+0.2, 0) AS bit),
		CAST(RAND(CHECKSUM(NEWID())) * 12 as tinyint),
		CAST(RAND(CHECKSUM(NEWID())) * 12 as tinyint),
		'' 
		 from Students where GroupId=@GroupId 

		Fetch next FROM Lessons_Cursor into @GroupId, @LessonId;
	END
	DEallocate Lessons_Cursor;

	update lessonsDetails set HomeMark=0, ClassMark=0 WHERE StudentPresence=0;
END

--exec spFillLessons
GO
/****** Object:  StoredProcedure [dbo].[spShowExamRollById]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spShowExamRollById]
@RollId int
AS
BEGIN
select ExamDate AS [Date],v_courses.LastName+' '+v_courses.FirstName AS Teacher,
	 	Subject, v_Students.[Group], 
		v_Students.LastName+' '+v_Students.Firstname AS Student,
		Mark

from examinationRolls JOIN ExaminationRollsLines ON ExaminationRolls.Id=ExaminationRollsLines.ExaminationRollId 
JOIN v_courses ON examinationRolls.CourseId=v_Courses.Id
JOIN v_students ON examinationRollsLines.StudentId=v_Students.Id
where ExaminationRolls.Id=@RollId;
END

GO
/****** Object:  StoredProcedure [dbo].[spShowResultsByGroup]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE proc [dbo].[spShowResultsByGroup]
@Group nvarchar(30)
AS
BEGIN
select ExamDate AS [Date],Subject,v_Students.LastName+' '+v_Students.Firstname AS Student,
		Mark
from examinationRolls JOIN ExaminationRollsLines ON ExaminationRolls.Id=ExaminationRollsLines.ExaminationRollId 
JOIN v_courses ON examinationRolls.CourseId=v_Courses.Id
JOIN v_students ON examinationRollsLines.StudentId=v_Students.Id
where v_courses.[Group]=@Group
Order by Subject, Student
END

-- exec spShowResultsByGroup 'ВНУ 1322'


GO
/****** Object:  StoredProcedure [dbo].[spTeachersReport]    Script Date: 19.06.2015 16:46:23 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE proc [dbo].[spTeachersReport]
@TeacherId int,
@StartDate date,
@EndDate date
AS
select ExecutionDate as [Date], PairNumber as [Pair], Rooms.Number AS Room, subjects.Name AS [Subject], Groups.Name AS [Group]
 from lessons join courses ON lessons.CourseId=courses.id 
 JOIN Rooms On lessons.RoomId=Rooms.Id 
 JOIN Subjects On subjects.Id=courses.subjectId 
 JOIN Groups On courses.GroupId=Groups.Id
 WHERE Courses.TeacherId=@TeacherId AND ExecutionDate BETWEEN @StartDate AND @EndDate;


-- exec spTeachersReport @TeacherId=1, @StartDate='2014-02-01', @EndDate='2014-03-01'
GO
USE [master]
GO
ALTER DATABASE [Step] SET  READ_WRITE 
GO
