<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="AspControls.Index" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <p>
                Background:<br />
                <asp:ListBox ID="lstBackgroundColor" Height="150" runat="server">
                    <asp:ListItem Selected="True">White</asp:ListItem>
                    <asp:ListItem>Gray</asp:ListItem>
                    <asp:ListItem>Red</asp:ListItem>
                    <asp:ListItem>Orange</asp:ListItem>
                    <asp:ListItem>Yellow</asp:ListItem>
                    <asp:ListItem>Green</asp:ListItem>
                    <asp:ListItem>Blue</asp:ListItem>
                    <asp:ListItem>Black</asp:ListItem>
                </asp:ListBox>
            </p>

            <p>
                ForeColor:<br />
                <asp:DropDownList ID="ddlForeColor" runat="server">
                    <asp:ListItem>White</asp:ListItem>
                    <asp:ListItem>Gray</asp:ListItem>
                    <asp:ListItem>Red</asp:ListItem>
                    <asp:ListItem>Orange</asp:ListItem>
                    <asp:ListItem>Yellow</asp:ListItem>
                    <asp:ListItem>Green</asp:ListItem>
                    <asp:ListItem>Blue</asp:ListItem>
                    <asp:ListItem Selected="True">Black</asp:ListItem>
                </asp:DropDownList>
            </p>
            <p>
                <asp:CheckBox ID="cbUpperCase" Text="Upper" runat="server" />
            </p>
            <p>
                <asp:Button ID="btnSetStyles" runat="server" Text="Set Label Styles" OnClick="btnSetStyles_Click" />
            </p>
            <asp:Label ID="lblSample" runat="server" Text="Label"></asp:Label>

        </div>
    </form>
</body>
</html>
