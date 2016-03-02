using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using Windows.Web.Http;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;
using Windows.UI.Popups;
using System.ComponentModel;
using System.Threading;

namespace SitemapGenerator.Models
{
    class SiteMap
    {
        public string SiteUrl { get; set; }
        private Uri mHostUri;
        public int NestingLevel { get; set; }
        public int PagesInProcess { get; set; }
        public int PagesDone { get; set; }
        public ObservableCollection<Uri> Links { get; set; }
        public SiteMap()
        {
            SiteUrl = String.Empty;
            NestingLevel = 3;
            Links = new ObservableCollection<Uri>();
            PagesInProcess = 0;
            PagesDone = 0;
        }
        public SiteMap(string url, int nestingLevel)
            :this()
        {
            SiteUrl = url;
            NestingLevel = nestingLevel;
        }

        public void Parse(CancellationToken cancellationToken)
        {
            if (!Uri.TryCreate(SiteUrl, UriKind.Absolute, out mHostUri))
                throw new Exception("Error: Incorrect Url");

            Links.Add(mHostUri);
            GetPageAsync(mHostUri, 1, cancellationToken);
        }

        public async void GetPageAsync(Uri requestUri, int currentNestingLevel, CancellationToken cancellationToken)
        {
            if (cancellationToken.IsCancellationRequested)
                return;

            PagesInProcess++;
            NotifyPropertiesUpdated(EventArgs.Empty);

            using (HttpClient httpClient = new HttpClient())
            {
                try
                {
                    string pageContent = await httpClient.GetStringAsync(requestUri);
                    FindLinks(pageContent, 1, cancellationToken);
                }
                catch
                {}               
                PagesInProcess--;
                PagesDone++;
                NotifyPropertiesUpdated(EventArgs.Empty);
            }

        }

        private void FindLinks(string source, int currentNestingLevel, CancellationToken cancellationToken)
        {
            if (cancellationToken.IsCancellationRequested)
                return;


            MatchCollection links = Regex.Matches(source, @"<a\s+(?:[^>]*?\s+)?href=\s*""([^""]*)""", RegexOptions.Singleline);
            ProcessFindedUrls(links, currentNestingLevel, cancellationToken);

            MatchCollection links2 = Regex.Matches(source, @"<a\s+.*?href=\s*'([^']*)'", RegexOptions.Singleline);
            ProcessFindedUrls(links2, currentNestingLevel, cancellationToken);
        }

        private void ProcessFindedUrls(MatchCollection links, int currentNestingLevel, CancellationToken cancellationToken)
        {
            foreach (Match link in links)
            {
                string linkString = link.Groups[1].Value;
                Uri newUri;
                if (Uri.TryCreate(mHostUri, linkString, out newUri))
                {
                    if (!Links.Contains<Uri>(newUri))
                    {
                        Links.Add(newUri);
                        if (newUri.ToString().StartsWith(SiteUrl) && (NestingLevel==0 ||NestingLevel>currentNestingLevel))
                        {
                            GetPageAsync(newUri, currentNestingLevel + 1, cancellationToken);
                        }
                    }
                }
            }
        }

        public event EventHandler PropertiesUpdated;
        protected void NotifyPropertiesUpdated(EventArgs e)
        {
            if (PropertiesUpdated != null)
                PropertiesUpdated(this, e);
        }
    }
}
