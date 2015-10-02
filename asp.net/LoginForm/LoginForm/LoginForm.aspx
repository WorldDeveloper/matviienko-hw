<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LoginForm.aspx.cs" Inherits="LoginForm.LoginForm" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Login</title>
    <style>
        .LastRow {
            padding: 30px 0;
        }

        #rbGender_0 {
            margin-left: 0;
        }

        .ErrorSummary {
            background-color: yellow;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <table>
                <tr>
                    <td>First name:</td>
                    <td>
                        <asp:TextBox ID="txtFirstName" runat="server"></asp:TextBox>
                        <asp:RequiredFieldValidator ControlToValidate="txtFirstName" Display="None" ID="RequiredFieldValidator1" runat="server" ErrorMessage="First name required!"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td>Last name:</td>
                    <td>
                        <asp:TextBox ID="txtLastName" runat="server"></asp:TextBox>
                        <asp:RequiredFieldValidator ControlToValidate="txtLastName" Display="None" ID="RequiredFieldValidator2" runat="server" ErrorMessage="Last name required!"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td>Login:</td>
                    <td>
                        <asp:TextBox ID="txtLogin" runat="server"></asp:TextBox>
                        <asp:RequiredFieldValidator ControlToValidate="txtLogin" Display="None" ID="RequiredFieldValidator3" runat="server" ErrorMessage="Login required!"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td>Password:</td>
                    <td>
                        <asp:TextBox ID="txtPassword" runat="server" TextMode="Password"></asp:TextBox>
                        <asp:RequiredFieldValidator ControlToValidate="txtPassword" Display="None" ID="RequiredFieldValidator4" runat="server" ErrorMessage="Password required!"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td>Reenter password:
                    </td>
                    <td>
                        <asp:TextBox ID="txtPasswordConfirmation" runat="server" TextMode="Password"></asp:TextBox>
                        <asp:CompareValidator ControlToValidate="txtPassword" ControlToCompare="txtPasswordConfirmation" Type="String" Operator="Equal" Display="None" ID="CompareValidator1" runat="server" ErrorMessage="Password mismatch"></asp:CompareValidator>
                        <asp:RegularExpressionValidator ControlToValidate="txtPassword" ValidationExpression=".{6}" Display="None" ID="RegularExpressionValidator1" runat="server" ErrorMessage="Password length must be at least 6 characters"></asp:RegularExpressionValidator>
                    </td>
                </tr>
                <tr>
                    <td>E-mail:</td>
                    <td>
                        <asp:TextBox ID="txtEmail" runat="server" TextMode="Email"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td>Age:</td>
                    <td>
                        <asp:TextBox ID="txtAge" runat="server" TextMode="Number" min="18" max="100" step="1"></asp:TextBox>
                        <asp:RequiredFieldValidator ControlToValidate="txtAge" Display="None" ID="RequiredFieldValidator5" runat="server" ErrorMessage="Age required!"></asp:RequiredFieldValidator>
                        <asp:RangeValidator MinimumValue="18" MaximumValue="100" Type="Integer" ControlToValidate="txtAge" Display="None" ID="RangeValidator1" runat="server" ErrorMessage="Age must be within the range 18-100"></asp:RangeValidator>
                    </td>
                </tr>
                <tr>
                    <td>Gender:</td>
                    <td>
                        <asp:RadioButtonList ID="rbGender" RepeatDirection="Horizontal" runat="server">
                            <asp:ListItem>Male</asp:ListItem>
                            <asp:ListItem>Female</asp:ListItem>
                            <asp:ListItem>Other</asp:ListItem>
                        </asp:RadioButtonList>
                        <asp:RequiredFieldValidator ControlToValidate="rbGender" Display="None" ID="RequiredFieldValidator6" runat="server" ErrorMessage="Gender required!"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td class="LastRow">
                        <asp:CheckBox ID="cbSubscribe" Text="Subscribe" runat="server" />
                    </td>
                    <td class="LastRow">
                        <asp:Button ID="btnSubmit" runat="server" Text="Submit" OnClick="btnSubmit_Click" />
                    </td>
                </tr>
            </table>
            <br />
            <asp:ValidationSummary ID="ValidationSummary1" HeaderText="There are some problems:" CssClass="ErrorSummary" runat="server" />
            <asp:Label ID="lblResult" runat="server" Text=""></asp:Label>
        </div>
    </form>
</body>
</html>
