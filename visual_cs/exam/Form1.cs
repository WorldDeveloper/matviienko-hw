using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace exam
{
    public partial class Form1 : Form
    {
        private FolderBrowserDialog mFolderBrowser;
        private string mPath;

        public Form1()
        {
            InitializeComponent();
            mFolderBrowser = new FolderBrowserDialog();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {

            DialogResult result = mFolderBrowser.ShowDialog();
            if (result == DialogResult.OK)
            {
                mPath = mFolderBrowser.SelectedPath;
                ListDirectory();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mPath = @"\\fs\Преподаватели\Загоруйко А\Public";

            if (Directory.Exists(mPath))
            {
                ListDirectory();
            }
            else
            {
                DialogResult result = mFolderBrowser.ShowDialog();
                if (result == DialogResult.OK)
                {
                    mPath = mFolderBrowser.SelectedPath;
                    ListDirectory();
                }
            }
        }

        private void ListDirectory()
        {
            TreeView1.ImageList = icons;
            TreeView1.ImageIndex = 0;
            TreeView1.SelectedImageIndex = 0;

            TreeView1.Nodes.Clear();
            var rootDirectoryInfo = new DirectoryInfo(mPath);
            TreeView1.Nodes.Add(CreateDirectoryNode(rootDirectoryInfo));
        }

        private TreeNode CreateDirectoryNode(DirectoryInfo directoryInfo)
        {
            var directoryNode = new TreeNode(directoryInfo.Name);
            directoryNode.ImageIndex = 1;
            directoryNode.SelectedImageIndex = 2;

            foreach (var directory in directoryInfo.GetDirectories())
            {
                if ((directory.Attributes & FileAttributes.Hidden) != FileAttributes.Hidden)
                    directoryNode.Nodes.Add(CreateDirectoryNode(directory));
            }

            foreach (var file in directoryInfo.GetFiles())
            {
                directoryNode.Nodes.Add(new TreeNode(file.Name));
            }

            return directoryNode;
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TreeNodeCollection nodes = TreeView1.Nodes;
            foreach (TreeNode node in nodes)
            {
                PrintRecursive(node);
            }
        }

        private void CopyFile(TreeNode node)
        {
            StringBuilder sb = new StringBuilder(node.FullPath.ToString());
            sb = sb.Replace(TreeView1.Nodes[0].Text, "");
            sb.Insert(0, mPath);

            string fileName = node.Text;
            string sourceFile = sb.ToString(); ;
            string targetPath = mPath + "\\copy";
            string destFile = System.IO.Path.Combine(targetPath, fileName);

            if (File.Exists(sourceFile))
            {
                if (!System.IO.Directory.Exists(targetPath))
                {
                    System.IO.Directory.CreateDirectory(targetPath);
                }

                System.IO.File.Copy(sourceFile, destFile, true);
            }
        }

        private void PrintRecursive(TreeNode treeNode)
        {
            if (treeNode.Checked == true) CopyFile(treeNode);
            foreach (TreeNode tn in treeNode.Nodes)
            {
                PrintRecursive(tn);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            TreeNodeCollection nodes = TreeView1.Nodes;
            foreach (TreeNode node in nodes)
            {
                PrintRecursive(node);
            }
        }
    }
}
