using SitemapGenerator.Models;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;
using Windows.UI.Popups;
using Windows.UI.Xaml;

namespace SitemapGenerator.ViewModels
{
    class SiteMapView : INotifyPropertyChanged
    {
        public SiteMapView()
        {
            SiteMap = new SiteMap();
            CreateCommandStartParsing();
            ResultsVisibility = Visibility.Collapsed;
            SiteMap.PropertiesUpdated += SiteMap_PropertiesUpdated;
        }

        private void SiteMap_PropertiesUpdated(object sender, EventArgs e)
        {
            UpdateProperties();
            if (PagesInProcess == 0)
            {
                IsCancel = false;
                NotifyPropertyChanged("CurrentButtonTitle");
                MessageDialog dialog = new MessageDialog("Parsing finished");
                var res = dialog.ShowAsync();
            }
        }

        public SiteMap SiteMap { get; set; }

        public string SiteUrl
        {
            get
            {
                return SiteMap.SiteUrl;
            }
            set
            {
                SiteMap.SiteUrl = value;
                NotifyPropertyChanged("SiteUrl");
            }
        }

        public int NestingLevel
        {
            get
            {
                return SiteMap.NestingLevel;
            }
            set
            {
                SiteMap.NestingLevel = value;
                NotifyPropertyChanged("NestingLevel");
            }
        }

        public ObservableCollection<Uri> Links
        {
            get
            {
                return SiteMap.Links;
            }
        }

        public int LinksCount
        {
            get
            {
                return SiteMap.Links.Count;
            }
        }

        public int PagesInProcess
        {
            get
            {
                return SiteMap.PagesInProcess;
            }
            private set
            {
                SiteMap.PagesInProcess = value;
                NotifyPropertyChanged("PagesInProcess");
            }
        }

        public int PagesDone
        {
            get
            {
                return SiteMap.PagesDone;
            }
            private set
            {
                SiteMap.PagesDone = value;
                NotifyPropertyChanged("PagesDone");
            }
        }

        public Visibility mResultsVisibility;
        public Visibility ResultsVisibility
        {
            get
            {
                return mResultsVisibility;
            }
            set
            {
                mResultsVisibility = value;
                NotifyPropertyChanged("ResultsVisibility");
            }
        }

        private bool mIsCancel;
        private bool IsCancel
        {
            get
            {
                return mIsCancel;
            }
            set
            {
                mIsCancel = value;
                NotifyPropertyChanged("InputEnabled");
            }
        }

        public bool InputEnabled {
        get
            {
                return !IsCancel;
            }
        }


        public string CurrentButtonTitle
        {
            get
            {
                if (IsCancel)
                    return "Cancel";
                else
                    return "Start";
            }
        }

        static CancellationTokenSource mCancellationSource;

        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }


        private ICommand mStartParsing;
        public ICommand StartParsing
        {
            get
            {
                return mStartParsing;
            }
        }

        private void CreateCommandStartParsing()
        {
            mStartParsing = new RelayCommand<string>(
                (p) =>
                {
                    if (p is string)
                    {
                        if (IsCancel)
                            CancelParsing();
                        else
                            BeginParsing();

                        NotifyPropertyChanged("CurrentButtonTitle");
                    }
                },
                (p) =>
                {
                    if (IsCancel)
                        return PagesInProcess>0;
                    else
                        return (p is string) && (!string.IsNullOrWhiteSpace(p.ToString()));
                }
                );
        }

        private void BeginParsing()
        {
            try
            {
                SiteMap = new SiteMap(SiteUrl, NestingLevel);
                SiteMap.PropertiesUpdated += SiteMap_PropertiesUpdated;

                mCancellationSource = new CancellationTokenSource();
                SiteMap.Parse(mCancellationSource.Token);
                ResultsVisibility = Visibility.Visible;
                IsCancel = true;
                UpdateProperties();
            }
            catch (Exception ex)
            {
                MessageDialog dialog = new MessageDialog(ex.Message);
                var result = dialog.ShowAsync();
                IsCancel = false;
            }
        }

        private void CancelParsing()
        {
            try
            {
                mCancellationSource.Cancel();
                IsCancel = false;

            }
            finally
            {
                mCancellationSource.Dispose();
            }
        }

        private void UpdateProperties()
        {
            NotifyPropertyChanged("Links");
            NotifyPropertyChanged("PagesDone");
            NotifyPropertyChanged("PagesInProcess");
            NotifyPropertyChanged("LinksCount");
        }
    }
}
