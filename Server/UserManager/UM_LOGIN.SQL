CREATE PROCEDURE UM_LOGIN
@strUserID VARCHAR(13),
@strPasswd VARCHAR(11),
@nServiceID INT,
@strIPAddr VARCHAR(16),
@wGameSerial SMALLINT
AS

DECLARE 
    @nCurServiceID INT,
    @strPasswd1 VARCHAR(11), 
    @strSerialPasswd VARCHAR(11), 
    @bLoginResult TINYINT, 
    @timeLogin SMALLDATETIME, 
    @wPrivateSerial SMALLINT
    @nValidDay INT, 
	@wSerial SMALLINT,
	@bCheckResult TINYINT, 
	@timeStart SMALLDATETIME, 
	@timeEnd SMALLDATETIME, 
	@nCurReg INT,
	@bSerialType TINYINT,
	@nMaxAccount INT,
	@nCurAccount INT

SELECT @strPasswd1=strPasswd, @wPrivateSerial = wSerial FROM NGSCUSER WHERE strUserID=@strUserID
IF (@strPasswd1 = NULL)
    BEGIN
    /* Unregistered User */
    SELECT @bLoginResult = 1
    END
ELSE
    BEGIN
    IF (@strPasswd1 <> @strPasswd)
        BEGIN
        /* Invalid Password */
        SELECT @bLoginResult = 2
        END
    ELSE
        BEGIN
        /* Check Duplicated User */
        SELECT @nCurServiceID = nServiceID FROM CURRENTUSER WHERE strUserID = @strUserID
		IF (@nCurServiceID <> NULL)
		    SELECT @bLoginResult = 3
		ELSE
		    BEGIN
		    /* Login Success */
            SELECT @bLoginResult = 0
            SELECT @timeLogin = GETDATE()
            UPDATE NGSCUSER SET timeLog=@timeLogin WHERE strUserID=@strUserID

            /* Check Serial Result Initialize */
            SELECT @bCheckResult = 1, @bSerialType = 0, @wSerial = NULL

            /* Check Private Serial */
            IF (@wPrivateSerial > 0)
                BEGIN
                /* Query Private Serial Table */
                SELECT @nValidDay = nValidDay, @timeStart = timeStart, @timeEnd = timeEnd, @nCurReg = nCurReg
                FROM SERIAL
                WHERE wSerial = @wPrivateSerial AND nMaxReg > 0 AND strPasswd <> NULL

                IF (@nValidDay <> NULL)
                    BEGIN
					/* Serial Code Exist */
	                IF (@nValidDay <> 0 AND @timeEnd > GETDATE ())
	                    BEGIN
						    /* Valid Serial Code */
	                        SELECT @bCheckResult = 0, @bSerialType = 1, @wSerial = @wPrivateSerial
	                    END
	                ELSE
	                    SELECT @bCheckResult = 4
                    END

                UPDATE NGSCUSER SET wSerial=NULL WHERE strUserID = @strUserID AND @bCheckResult <> 0
                END /* End of Check Private Serial */

            /* Check GameRoom Serial*/
            IF (@bCheckResult <> 0 AND @wGameSerial > 0)
                BEGIN
				SELECT @strSerialPasswd = SUBSTRING(@strIPAddr, 1, 10)
                SELECT @nValidDay = nValidDay, @strPasswd1 = strPasswd, @timeStart = timeStart, @timeEnd = timeEnd, @nCurReg = nCurReg
                FROM SERIAL
                WHERE wSerial = @wGameSerial AND nMaxReg = 0 AND nValidDay <> 0 AND (strPasswd = NULL OR (strPasswd = @strSerialPasswd AND timeEnd > GETDATE ()))

                IF (@nValidDay <> NULL)
					/* Serial Code Exist */
                    BEGIN
	                IF (@strPasswd = NULL)
	                    BEGIN
	                    /* 사용하지 않은 과금번호의 경우 */
	                    IF (@nValidDay > 0)
	                        BEGIN
		                    /* 기간 정액제의 경우 */
		                    SELECT @timeStart = @timeLogin, @timeEnd = DATEADD(dd, @nValidDay, @timeLogin)
		                    UPDATE SERIAL 
							SET strPasswd = @strSerialPasswd, timeStart = @timeLogin, timeEnd = @timeEnd
		                    WHERE wSerial = @wGameSerial
	                        END
	                    ELSE
	                        BEGIN
		                    /* 시간 정액제의 경우 */
		                    SELECT @timeStart = @timeLogin, @timeEnd = DATEADD(mm, 6, @timeLogin)
		                    UPDATE SERIAL 
							SET strPasswd = @strSerialPasswd, timeStart = @timeLogin, timeEnd = @timeEnd
							WHERE wSerial = @wGameSerial
	                        END
	                    END
                    SELECT @bCheckResult = 0, @bSerialType = 2, @wSerial = @wGameSerial
                    END
                END /* End of Check GameRoom Serial */

			/* Check Serial Code Duplicate */
			IF (@bCheckResult = 0)
			    BEGIN
				/* Get Max Account */
				IF (@bSerialType = 1 OR @nCurReg < 1)
					SELECT @nMaxAccount = 1
				ELSE
					SELECT @nMaxAccount = @nCurReg
				/* Get Current Account */
				SELECT @nCurAccount = COUNT(*) FROM CURRENTUSER WHERE wSerial = @wSerial

				/* Check Account */
				IF (@nMaxAccount <= @nCurAccount)
				    SELECT @bCheckResult = 1, @wSerial = NULL
				END

            /* Current User Insert */
			INSERT INTO CURRENTUSER VALUES (@strUserID, @nServiceID, @timeLogin, @wSerial, @strIPAddr)

            END /* End of Login Success */
        END
    END

SELECT @bLoginResult, @timeLogin, @bCheckResult, @wSerial, @timeStart, @timeEnd
RETURN @@error

GO
