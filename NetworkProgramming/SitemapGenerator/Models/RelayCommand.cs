using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SitemapGenerator.Models
{
    public class RelayCommand<T> : ICommand
    {
        readonly Action<T> mExecute = null;
        readonly Predicate<T> mCanExecute = null;
        public event EventHandler CanExecuteChanged;

        public RelayCommand(Action<T> execute)
            : this(execute, null)
        {
        }

        public RelayCommand(Action<T> execute, Predicate<T> canExecute)
        {
            if (execute == null)
                throw new ArgumentNullException("execute");

            mExecute = execute;
            mCanExecute = canExecute;
        }

        public bool CanExecute(object parameter)
        {
            return mCanExecute == null ? true : mCanExecute((T)parameter);
        }


        public void Execute(object parameter)
        {
            mExecute((T)parameter);
        }
    }
}
