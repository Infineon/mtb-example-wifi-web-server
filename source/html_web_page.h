/******************************************************************************
* File Name: html_web_page.h
*
* Description: This file contains the HTML pages that the server will host and
*              macros required for http transaction.
*
********************************************************************************
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef HTML_WEB_PAGE_H_
#define HTML_WEB_PAGE_H_

/*******************************************************************************
* Macros
******************************************************************************/
/* Company Logo */
#define LOGO \
    "<style>" \
        ".container { " \
            "position: relative; " \
        "}" \
        ".topleft{" \
            "position: absolute; " \
            "top: 8px; " \
            "left: 16px; "\
            "font-size: 18px; " \
        "}" \
        "img {" \
            "width : auto; " \
            "height: auto;" \
        "}" \
    "</style>" \
    "<div class=\"container\"> "\
    "<img alt=\"logo.png\" "\
    "src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAATkAAABcBAMAAADngd+fAA" \
           "AAD1BMVEX///8VWJbiOlVtkLHIxNm177myAAAEAklEQVR4AezBgQAAAACAoP2pF6kCA" \
           "ABmxgxw29VhMO4WHwArHABlOQBpOIAJvv+ZnmPolnbbwn9Dev2EPNJK3m+fHZPRlmRf" \
           "JMKvh7aRwSvKXAsMryg0NnhFdcmKyvCSIupf1DgVErnzjJMkp8KJ0p2WLJJqhtPkR6L" \
           "hPfvfPOxIdSZe9iHS9JGdV/5Lj+xiOEVX7z2851qIkHr4rRbadFqrKNz4sYpOkAY4qD" \
           "XNX1unmk6zDtM7nZLR9Fu6hehU89CGcEc1HcJhurdHOqrFp1gXoKL7sqp80LuObPNHR" \
           "0V9NQHQgsZ6MohmbnYdG10XOxr0xiVIvV6JGGAx2LKjMUp0LbqF9nXcS4tEk+aO/aI3" \
           "EPdA5dcwLORwbhYWNjpSleiAesvRW5OzfQP4ZaOvt4f0kRKY5iIquEpAQJPeKKSuNjr" \
           "LrmGeWoUdKzrWON/pBriQUF8cUS6rVcM7EqlWUrp4VZSZeHErcVkxDSJIcxw6DY3RlS" \
           "u6qSPWfGB0rlyLK2vSq99iw7tHYdn9SJqIYOn1Pk5ArAGQ4OI6/XRoth3c6RgrumFHW" \
           "4Z9qfa1vENhqNT1G91C7hMdd4Xucozu8kHXP9E5pOkrOkxpnW+3Oa1p5R2HXA27FiIQ" \
           "TT5A3Ohwo7PJgJbuD96RaqNzn+lu6e2W0k1/vFUDZVLsaaMnoysf9+pdAbMudPr9Qlz" \
           "2EP8zXX+ULhU85dPr3TvTYMs4CG90qLHes7rEYl6n4U/eORH5wbtk3qW3is7U0YQidz" \
           "ogLnRDAes1p5tA1xYODONvvTNU+IYOtO20qKkInuimZLbvfWd0pSPjFDWzAVsu1NCiG" \
           "3/cs6qDe7aic3C50yFtdD0UusXy2EQZOge6bM278L13eiHf593UnHdIpr2IVDx/ors4" \
           "8647Nu/s/PS9dxcb55FWmo54B7RrMhct21LT9epX9ayQOLQPUOO3dLg/z4jgEF2kTfv" \
           "N9pyt6dC+stCDudtsvHCn657oLDvrmmZoVbY+fA5I1RmlriwSG123obsjR2OGbyWsAe" \
           "Xw+c7ES32++1JoyaEpr4J/kDTPxhOg6az/K0Y4rEczuvRIt9JjtbIwewx5CygIeQyIE" \
           "vLoOaCwHDHvMB6OT5V9Si8fAlXAEHzmMAbPOWD2cMV8zXqFEHL2oxwxz/NBuAA/a42b" \
           "Ukyg8tkrXQjjqDBidNd89Uo3+qx0DE3lw3jY7FBMd7GlDlLolEV8HtU29c5flVKCmoq" \
           "Z4Tw8+1sP4vHZ72SbxhlcG68UVgBOxWvZlw8PHhGBc3X1JvneNx/+75faX79zx/wC75" \
           "SNwRSC4MYlcv/I1i/C96QALyH8ClDgdYTy4Jr81x4cEwAAACAMsn9qM+wHlgEAAADAA" \
           "To83zvHyP+JAAAAAElFTkSuQmCC\" /> " \
           "<div class=\"topleft\"></div> " \
    "</div>"

/* Landing page, user input Wi-Fi network and credentials */
#define HTTP_SOFTAP_STARTUP_WEBPAGE \
              "<!DOCTYPE html>" \
              "<html>" \
              "<head>" \
              "<title>Wi-Fi Web Server Demo</title>" \
              "</head>" LOGO \
              "<body>" \
                "<h1 style=\"text-align: center\" >Web Server Demo - Home Page</h1>" \
                "<form method=\"post\">" \
                    "<fieldset>" \
                        "<legend>Enter Credentials</legend>" \
                        "<label><b>SSID </b></label></br>"\
                        "<input type=\"text\" placeholder=\"Enter SSID\" name=\"SSID\" size=\"30\" /></br></br>" \
                        "<label><b> Password</b></label></br>"\
                        "<input type=\"password\" placeholder=\"Enter Password\" name=\"Password\" size=\"30\" minlength=\"8\" /></br></br>" \
                        "<input type=\"submit\" name=\"submit\" value=\"Connect to Wi-Fi\"/></br></br>" \
                    "</fieldset>" \
                    "</br>" \
                "</form>" \
                "<form action=\"/wifi_scan_form\" method=\"get\">" \
                    "<fieldset>" \
                        "<input type=\"submit\" name=\"submit\" value=\"Scan for Wi-Fi Access Points\"/></br></br>" \
                    "</fieldset>" \
                    "</br>" \
                "</form>" \
              "</body>" \
              "</html>"

/* HTML Page - Indicates scan for available APs is in progress.*/
#define WIFI_SCAN_IN_PROGRESS \
    "<html>" \
    "<body>" \
    "<h1 id=\"wifi_scan_stat\">Scanning for available APs. Please wait...</h1>" \
    "</body>" \
    "</html>"

/* HTML Page - Lists available APs along with LogIn option.*/
#define SOFTAP_SCAN_START_RESPONSE \
    "<html>" \
    "<script>" \
    "function wifi_scan(){ " \
    "var wifi_obj = document.getElementById(\"wifi_scan_stat\");" \
    "wifi_obj.remove();" \
    "}" \
    "wifi_scan();" \
    "</script>" \
    "<head>" \
    "<title>AP Scan Status</title>" \
    "</head>" \
    "<body>" \
      "<h1>Available AP List - LogIn Page </h1>" \
      "<p>The available access points are listed below. Please enter appropriate \
      credentials and click the <i><b>Connect to Wi-Fi</b></i> button.</p>" \
      "<textarea readonly rows=\"4\" cols=\"50\" style=\"font-size:" \
      "large; color: rgb(11, 11, 11); background-color: rgb(232, 221, 238);" \
      "width: 450px; height: 180px;\">"


#define SOFTAP_SCAN_INTERMEDIATE_RESPONSE    "</textarea></body>"

#define SOFTAP_SCAN_END_RESPONSE \
    "<body>" \
    "</br></br>" \
    "<form action=\"/\" method=\"post\">" \
       "<fieldset>" \
            "<legend>Enter Credentials</legend>" \
            "<label><b>SSID </b></label></br>"\
            "<input type=\"text\" placeholder=\"Enter SSID\" name=\"SSID\" size=\"30\" /></br></br>" \
            "<label><b> Password</b></label></br>"\
            "<input type=\"password\" placeholder=\"Enter Password\" name=\"Password\" size=\"30\" minlength=\"8\" /></br></br>" \
            "<input type=\"submit\" name=\"submit\" value=\"Connect to Wi-Fi\"/></br></br>" \
        "</fieldset>" \
    "</form>" \
    "</center>" \
    "</body>" \
    "</html>"

/* HTML Page - Indicates connecting to AP whose credentials are entered is in progress.*/
#define WIFI_CONNECT_IN_PROGRESS \
    "<html>" \
    "<body>" \
    "<h1 id=\"wifi_stat\">Trying to connect to Wi-Fi. Please wait...</h1>" \
    "</body>" \
    "</html>"

/* HTML Page - Indicates Wi-Fi connection status.*/
#define WIFI_CONNECT_RESPONSE_START \
    "<html>" \
    "<script>" \
    "function wifi_cnt(){ " \
    "var wifi_obj = document.getElementById(\"wifi_stat\");" \
    "wifi_obj.remove();" \
    "}" \
    "wifi_cnt();" \
    "</script>" \
    "<body>" 

#define WIFI_CONNECT_FAIL_RESPONSE_END \
    "<h1>Failed to connect to Wi-Fi</h1>" \
    "<form action=\"/\" method=\"get\">" \
        "<fieldset>" \
            "<p>Click the button to redirect to homepage...</p>" \
            "<input type=\"submit\" name=\"submit\" value=\"Return to Home Page\"/></br></br>" \
        "</fieldset>" \
        "</br>" \
    "</form>" \
    "</body>" \
    "</html>"

#define WIFI_CONNECT_SUCCESS_RESPONSE_END \
    "<h1>Successfully connected to Wi-Fi</h1>" \
    "<form action=\"/\" method=\"get\">" \
        "<fieldset>" \
            "<p>Click the button to redirect to homepage...</p>" \
            "<input type=\"submit\" name=\"submit\" value=\"Return to Home Page\"/></br></br>" \
        "</fieldset>" \
        "</br>" \
    "</form>" \
    "<form action=\"/wifi_scan_form\" method=\"post\">" \
        "<fieldset>" \
            "<input type=\"submit\" name=\"submit\" value=\"Display Device Data\"/></br></br>" \
        "</fieldset>" \
    "</form>" \
    "</body>" \
    "</html>"

#define HTTP_DEVICE_DATA_REDIRECT_WEBPAGE \
    "<!DOCTYPE html>" \
    "<html>" \
        "<head>" \
        "<title>Device Data - Redirect Page</title>" \
        "</head>" \
        "<body>" \
            "<h1>Device Data - Redirect page </h1>" \
            "<p>" \
                "To view the device data please connect your PC to the same Wi-Fi network to which " \
                 "you have connected the device. Open the web browser of your choice and enter " \
                 "the URL http://<i><b>IP address</i></b>:80, where <i><b>IP address</i></b> is " \
                 "the one that is displayed on the UART terminal." \
            "</p>" \
        "</body>" \
    "</html>"

/* HTML Device Data Page - Data  */
#define SOFTAP_DEVICE_DATA \
        "<!DOCTYPE html> " \
        "<html>" \
        "<head><title>Wi-Fi Web Server Demo Device Status</title></head>" \
        "<body>" \
            "<h1 style=\"text-align: center\" > Device Data Logger </h1>" LOGO \
            "<br><br>" \
            "<p>Click to increase or decrease duty cycle</p>" \
            "<button type=\"button\" onclick=\"increase()\" id=\"increase_btn\">Increase</button> " \
            "<button type=\"button\" onclick=\"decrease()\" id=\"decrease_btn\">Decrease</button> " \
            "<br><br>" \
            "<br><br>" \
            "<div id=\"device_data\" value=\"100\"></div>" \
            "<script>" \
                " function btn_disable_function() {" \
                " var increase_btn_id = document.getElementById(\"increase_btn\");" \
                " var decrease_btn_id = document.getElementById(\"decrease_btn\");" \
                " increase_btn_id.innerText = \"Please Wait...\";" \
                " decrease_btn_id.innerText = \"Please Wait...\";" \
                " increase_btn_id.disabled = true;" \
                " decrease_btn_id.disabled = true;" \
                " setTimeout(function()" \
                " {" \
                    " increase_btn_id.innerText = \"Increase\";" \
                    " decrease_btn_id.innerText = \"Decrease\";" \
                    " increase_btn_id.disabled = false;" \
                    " decrease_btn_id.disabled = false;" \
                    " },1000);" \
                " }" \
            "function increase() { " \
                " btn_disable_function();" \
                " var xhttp = new XMLHttpRequest(); "\
                " xhttp.onreadystatechange = function() { "\
                    "   if (this.readyState === 4 && this.status == 200) { " \
                        "   } "\
                    "}; "\
                    "xhttp.open(\"POST\", \"/\", true); "\
                    "xhttp.setRequestHeader(\"Content-type\", \"application/x-www-form-urlencoded\"); "\
                    "xhttp.send(\"Increase\");"\
            "} "\
            "function decrease() { " \
                "  btn_disable_function();" \
                "  var xhttp = new XMLHttpRequest(); " \
                "  xhttp.onreadystatechange = function() { " \
                    "    if (this.readyState === 4 && this.status == 200) { " \
                    "    } " \
                    "  }; " \
                    "xhttp.open(\"POST\", \"/\", true); " \
                    "xhttp.setRequestHeader(\"Content-type\", \"application/x-www-form-urlencoded\"); "\
                    "xhttp.send(\"Decrease\"); " \
            "} "\
        "if(typeof(EventSource) !== \"undefined\") {" \
            "var source = new EventSource(\"/events\");" \
            "source.onmessage = function(event) {" \
                "document.getElementById(\"device_data\").innerHTML = event.data;" \
                "  };" \
        "} else {" \
            "document.getElementById(\"device_data\").innerHTML = \"Sorry, your browser does not support server-sent events...\";" \
        "}" \
        "</script>" \
        "</body>" \
        "</html>"

#endif /* HTTP_PAGES_H_ */

/* [] END OF FILE */