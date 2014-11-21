function Test() {
    this.mQuestions = ["2+2=4?", "4-2=3?", "2*2=4?"];
    this.mAnswers = [true, false, true];
    this.mUserAnswers = [];
    this.mGrade = 0;
    this.mUserName = getCookie("username");
    this.mAttemptsNumber = parseInt(getCookie("attemptsNumber"));
    if (isNaN(this.mAttemptsNumber)) this.mAttemptsNumber = 0;


    this.IsCookie = function () {
        setCookie("TestCookie", "Yes", 1);
        if (getCookie("TestCookie") == "") {
            alert("Please enable cookies and reload this page.");
            return false;
        }
        return true;
    }

    this.PassTest = function () {
        if (!this.IsCookie()) return;

        if (this.mAttemptsNumber >= 5) return;

        this.mUserAnswers = [];
        for (var i = 0; i < this.mQuestions.length; ++i) {
            this.mUserAnswers.push(confirm(this.mQuestions[i]));
        }

        setCookie("attemptsNumber", 1+this.mAttemptsNumber, 365);
    }

    this.ShowResult = function () {
        document.open();
        if (this.mUserName != "") {
            document.write("Welcome, " + this.mUserName + "!<br />");
            document.write("Your previous grade: " + getCookie("grade") + "%<br /><br />");
        }

        if (this.mUserName == "") {
            while (!this.mUserName) {
                this.mUserName = prompt("Please enter your name:", "");
            }
            setCookie("username", this.mUserName, 365);
        }

        if (this.mAttemptsNumber < 5) {

            if (this.mUserAnswers.length != this.mQuestions.length) {
                var error = "Test hasn't been passed.";
                document.write("<b>" + error + "</b>");
                alert(error);
                return;
            }
            setCookie("grade", this.mGrade, 365);
            
            document.write("<table><tr><th>Question</th><th>Your answer</th><th>Correct answer</th></tr>");
            for (var i = 0; i < this.mQuestions.length; ++i) {
                var trClass = "incorrect";
                if (this.mAnswers[i] == this.mUserAnswers[i]) trClass = "correct";

                document.write("<tr class='" + trClass + "'><td>" + this.mQuestions[i] + "</td><td>" + this.mUserAnswers[i] + "</td><td>" + this.mAnswers[i] + "</td></tr>");
                this.mGrade += (this.mUserAnswers[i] == this.mAnswers[i]);
            }
            document.write("</table>");

            this.mGrade = Math.round(this.mGrade * 1000 / this.mQuestions.length) / 10;
            var output = "Your current grade is " + this.mGrade + "% out of 100%";
            document.write("<br /><b>" + output + "</b>");           

            alert("Congratulate you, " + this.mUserName + "!\nYour grade is " + this.mGrade + "% out of 100%");
        }
        else {
            document.write("You have exhausted all possibilities.");
            alert("You have exhausted all possibilities.");
        }

        document.close();
    }
}

function setCookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
    var expires = "expires=" + d.toUTCString();
    document.cookie = cname + "=" + cvalue + "; " + expires;
}

function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') c = c.substring(1);
        if (c.indexOf(name) != -1) return c.substring(name.length, c.length);
    }
    return "";
}

function checkCookie() {
    var username = getCookie("username");
    if (username != "") {
        alert("Congratulations, " + username);
    } else {
        username = prompt("Please enter your name:", "");
        if (username != "" && username != null) {
            setCookie("username", username, 365);
        }
    }
}


