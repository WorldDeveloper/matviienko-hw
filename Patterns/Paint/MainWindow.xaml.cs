using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Ink;
using Microsoft.Win32;

namespace Paint
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string mFileName;

        public MainWindow()
        {
            InitializeComponent();
            mFileName = string.Empty;
            this.Title = "New painting";
            UpdateCbPenSize();
            cbPenSize.SelectedIndex = 1;
            mFigureType = "Pen";

            //icCanvas.EditingMode = InkCanvasEditingMode.None;
        }

        private void UpdateCbPenSize()
        {
            if (cbPenSize == null)
                return;

            int selectedIndex = cbPenSize.SelectedIndex;
            cbPenSize.Items.Clear();
            for (int i = 1; i < 20; ++i)
            {

                Ellipse el = new Ellipse();
                el.Tag = i;
                el.Width = i;
                el.Height = i;
                el.Fill = new SolidColorBrush(icCanvas.DefaultDrawingAttributes.Color);
                el.VerticalAlignment = VerticalAlignment.Center;
                cbPenSize.Items.Add(el);
            }
            cbPenSize.SelectedIndex = selectedIndex;
        }

        private void btnErase_Click(object sender, RoutedEventArgs e)
        {
            icCanvas.EditingMode = InkCanvasEditingMode.EraseByPoint;
        }

        private void btnDraw_Click(object sender, RoutedEventArgs e)
        {
            SetDrawMode();
        }

        private void btnSelect_Click(object sender, RoutedEventArgs e)
        {
            icCanvas.EditingMode = InkCanvasEditingMode.Select;
        }

        private void cbColor_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string selectedColor = (cbColor.SelectedItem as Rectangle).Tag.ToString();
            icCanvas.DefaultDrawingAttributes.Color = (Color)ColorConverter.ConvertFromString(selectedColor);
            UpdateCbPenSize();
        }

        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            icCanvas.Strokes.Clear();
            icCanvas.Children.Clear();
        }

        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "My paintings (.MyBmp)|*.MyBmp";
            dlg.FilterIndex = 0;

            bool result = (bool)dlg.ShowDialog();
            if (result == false)
                return;

            btnClear_Click(sender, e);
            mFileName = dlg.FileName;

            using (FileStream fs = new FileStream(mFileName, FileMode.Open, FileAccess.Read))
            {
                StrokeCollection strokes = new StrokeCollection(fs);
                icCanvas.Strokes = strokes;
            }

            this.Title = System.IO.Path.GetFileName(mFileName);
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(mFileName))
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "My paintings (.MyBmp)|*.MyBmp";
                saveFileDialog.FilterIndex = 0;

                if (saveFileDialog.ShowDialog() == false)
                    return;

                mFileName = saveFileDialog.FileName;
            }
            icCanvas.UpdateLayout();

            using (FileStream fs = new FileStream(mFileName, FileMode.Create))
            {
                icCanvas.Strokes.Save(fs);
            }

            this.Title = System.IO.Path.GetFileName(mFileName);
        }

        private void btnNew_Click(object sender, RoutedEventArgs e)
        {
            mFileName = string.Empty;
            btnClear_Click(sender, e);
            this.Title = "New painting";

        }

        private void btnSaveAs_Click(object sender, RoutedEventArgs e)
        {
            string prevFileName = mFileName;
            mFileName = string.Empty;

            btnSave_Click(sender, e);

            if (string.IsNullOrWhiteSpace(mFileName))
                mFileName = prevFileName;
        }

        private void cbPenSize_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Ellipse penSize = cbPenSize.SelectedItem as Ellipse;
            if (penSize == null)
                return;

            icCanvas.DefaultDrawingAttributes.Width = penSize.Width;
            icCanvas.DefaultDrawingAttributes.Height = penSize.Height;
        }

        private void cbTool_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBoxItem selectedTool = cbTool.SelectedItem as ComboBoxItem;
            if (selectedTool== null)
                return;

            mFigureType= selectedTool.Content.ToString();
            SetDrawMode();
        }

        private void SetDrawMode()
        {
            switch (mFigureType)
            {
                case "Pen":
                    icCanvas.EditingMode = InkCanvasEditingMode.Ink;
                    break;
                default:
                    icCanvas.EditingMode = InkCanvasEditingMode.None;
                    break;
            }
        }
    }
}
