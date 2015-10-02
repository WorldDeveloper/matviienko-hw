<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="PowerCalc.Index" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
       
        <asp:TextBox ID="txtNumber" placeholder="Number"  runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="txtNumberRequiredFieldValidator" runat="server" ErrorMessage="*Required Field!" ControlToValidate="txtNumber" ForeColor="Red" Display="Dynamic"></asp:RequiredFieldValidator>
        <asp:CompareValidator ID="txtNumberCompareValidator" runat="server" ErrorMessage="*Enter a number" ControlToValidate="txtNumber" Operator="DataTypeCheck" Type="Double" ForeColor="Red" Display="Dynamic" />
        <br />
        <asp:TextBox ID="txtPower" placeholder="Power" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="txtPowerRequiredValidator" runat="server" ErrorMessage="*Required Field!" ControlToValidate="txtPower" ForeColor="Red" Display="Dynamic"></asp:RequiredFieldValidator>
        <asp:CompareValidator ID="txtPowerCompareValidator" runat="server" ErrorMessage="*Enter a Number" ControlToValidate="txtPower" Operator="DataTypeCheck" Type="Double" ForeColor="Red" Display="Dynamic" />

        <br />
        <asp:Button ID="btnCalc"  Text="Calculate" OnClick="btnCalc_Click" runat="server" />
        <br />
        <br />
        <asp:Label ID="lblResult" Text="" style="font-weight:bold;" runat="server"></asp:Label>
    </div>
    </form>
</body>
</html>
