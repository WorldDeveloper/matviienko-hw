<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <html>
      <head>
        <link href="styles.css" rel="stylesheet" type="text/css" />
      </head>
      <body>
        <h2>Timetable</h2>
        <table>
          <tr>
            <th>Train ID</th>
            <th>Dispatch station </th>
            <th>Departure time</th>
            <th>Arrival station</th>
            <th>Arrival time</th>
            <th>Notes</th>
          </tr>
          <xsl:for-each select="railway/routes/route/stations">
            <tr>
              <td>
                <xsl:value-of select="substring(../@trainID, 2)"/>
              </td>
              <td>
                <xsl:value-of select="id(station[1]/@id)"/>
              </td>
              <td>
                <xsl:value-of select="station[1]/departureTime"/>
              </td>
              <td>
                <xsl:value-of select="id(station[last()]/@id)"/>
              </td>
              <td>
                <xsl:value-of select="station[last()]/arrivalTime"/>
              </td>
              <td>
                <xsl:value-of select="../description"/>
              </td>
            </tr>
          </xsl:for-each>
        </table>

        <h2>List of trains passing through the station "Minsk"</h2>
        <table>
          <tr>
            <th>Train ID</th>
            <th>Arrival Time</th>
            <th>Departure Time</th>
            <th>Notes</th>
          </tr>
          <xsl:for-each select="railway/routes/route/stations/station">
            <xsl:if test="id(@id)='Мінськ'">
              <tr>
                <td>
                  <xsl:value-of select="substring(../../@trainID,2)"/>
                </td>
                <td>
                  <xsl:value-of select="arrivalTime"/>
                </td>
                <td>
                  <xsl:value-of select="departureTime"/>
                </td>
                <td>
                  <xsl:value-of select="../../description"/>
                </td>
              </tr>
            </xsl:if>
          </xsl:for-each>
        </table>

        <h2>List of trains passing throught the station "Vinnytsa"</h2>
        <table>
          <tr>
            <th>Train ID</th>
            <th>Arrival Time</th>
            <th>Departure Time</th>
            <th>Notes</th>
          </tr>
          <xsl:for-each select="railway/routes/route/stations/station">
            <xsl:if test="id(@id)='Вінниця'">
              <tr>
                <td>
                  <xsl:value-of select="substring(../../@trainID,2)"/>
                </td>
                <td>
                  <xsl:value-of select="arrivalTime"/>
                </td>
                <td>
                  <xsl:value-of select="departureTime"/>
                </td>
                <td>
                  <xsl:value-of select="../../description"/>
                </td>
              </tr>
            </xsl:if>
          </xsl:for-each>
        </table>

        <h2>List of stations being passed by the train "24"</h2>
        <table>
          <tr>
            <th>Station</th>
            <th>Arrival Time</th>
            <th>Departure Time</th>
            <th>Notes</th>
          </tr>
          <xsl:for-each select="railway/routes/route">
            <xsl:if test="@trainID='t24'">
              <xsl:for-each select="./stations/station">
                <tr>
                  <td>
                    <xsl:value-of select="id(@id)"/>
                  </td>
                  <td>
                    <xsl:value-of select="arrivalTime"/>
                  </td>
                  <td>
                    <xsl:value-of select="departureTime"/>
                  </td>
                  <td>
                    <xsl:value-of select="../../description"/>
                  </td>
                </tr>
              </xsl:for-each>
            </xsl:if>
          </xsl:for-each>
        </table>

        <h2>List of stations being passed by the train "106"</h2>
        <table>
          <tr>
            <th>Station</th>
            <th>Arrival Time</th>
            <th>Departure Time</th>
            <th>Notes</th>
          </tr>
        <xsl:for-each select="railway/routes/route">
          <xsl:if test="@trainID='t106'">              
            <xsl:for-each select="./stations/station">
               <tr>
                 <td>
                   <xsl:value-of select="id(@id)"/>
                 </td>
                 <td>
                   <xsl:value-of select="arrivalTime"/>
                 </td>
                 <td>
                   <xsl:value-of select="departureTime"/>
                 </td>
                 <td>
                   <xsl:value-of select="../../description"/>
                 </td>
              </tr>
            </xsl:for-each>
          </xsl:if>
        </xsl:for-each>
        </table>
        
      </body>
    </html>
  </xsl:template>  
</xsl:stylesheet>

