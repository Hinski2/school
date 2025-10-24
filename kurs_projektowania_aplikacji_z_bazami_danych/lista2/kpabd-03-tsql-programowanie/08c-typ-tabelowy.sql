USE Test;

DROP TABLE IF EXISTS Survey;
GO

CREATE TABLE Survey (Respondent INT, Answer INT, Rate INT);
GO

DECLARE @i INT, @j INT
SET @i=0;
WHILE (@i<10)
BEGIN
    SET @j=0;
	WHILE (@j<10)
	BEGIN
		INSERT INTO Survey VALUES(@i,@j, CAST(RAND()*10+1 AS INT))
        SET @j=@j+1
	END
    SET @i=@i+1
END
GO

DROP TYPE IF EXISTS SurveyRatingType;
GO

CREATE TYPE SurveyRatingType AS TABLE (Rate INT);
GO

DROP PROCEDURE IF EXISTS CalculateAvgRate;
GO

CREATE PROCEDURE CalculateAvgRate @SurveyRating SurveyRatingType READONLY
AS
BEGIN
	SELECT ROUND(AVG(CAST(Rate AS FLOAT)), 2) AS [Average Rating] FROM @SurveyRating;
END
GO

DECLARE @rates SurveyRatingType
INSERT INTO @rates SELECT Rate FROM Survey;
EXEC CalculateAvgRate @rates;
GO

DROP PROCEDURE IF EXISTS CalculateAvgRate;
DROP TABLE IF EXISTS Survey;
DROP TYPE IF EXISTS SurveyRatingType;
GO