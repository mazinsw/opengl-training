#include "choosedlg.h"
#include <commdlg.h>
#include <string.h>

CommonDialog::Options::Options()
{
    flags = 0;
}

unsigned long int CommonDialog::Options::evalEnum(DialogOptions option)
{
    switch(option)
    {
    case dlgOpt_enableSizing:
        return OFN_ENABLESIZING;
    case dlgOpt_explorer:
        return OFN_EXPLORER;
    case dlgOpt_extensionDifferent:
        return OFN_EXTENSIONDIFFERENT;
    case dlgOpt_fileMustExist:
        return OFN_FILEMUSTEXIST;
    case dlgOpt_hideReadOnly:
        return OFN_HIDEREADONLY;
    case dlgOpt_noChangeDir:
        return OFN_NOCHANGEDIR;
    case dlgOpt_noNetworkButton:
        return OFN_NONETWORKBUTTON;
    case dlgOpt_noReadOnlyReturn:
        return OFN_NOREADONLYRETURN;
    case dlgOpt_pathMustExist:
        return OFN_PATHMUSTEXIST;
    case dlgOpt_readOnly:
        return OFN_READONLY;
    }
    return 0;
}

unsigned long int CommonDialog::Options::getFlags()
{
    return flags;
}

CommonDialog::Options& CommonDialog::Options::operator=(DialogOptions option)
{
    flags = evalEnum(option);
    return *this;
}

CommonDialog::Options& CommonDialog::Options::operator+=(DialogOptions option)
{
    flags |= evalEnum(option);
    return *this;
}

CommonDialog::Options& CommonDialog::Options::operator-=(DialogOptions option)
{
    flags &= ~evalEnum(option);
    return *this;
}

CommonDialog::CommonDialog()
{
    filterIndex = 0;
}

void CommonDialog::prepare(OPENFILENAME& ofn)
{
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.nFilterIndex = filterIndex + 1;
    ofn.lpstrTitle = title.c_str();
    ofn.lpstrInitialDir = initialDir.c_str();
    ofn.Flags = options.getFlags();
}

Strings& CommonDialog::getFilter()
{
    return filter;
}

String CommonDialog::getTitle()
{
    return title;
}

void CommonDialog::setTitle(String title)
{
    this->title = title;
}

int CommonDialog::getFilterIndex()
{
    return filterIndex;
}

void CommonDialog::setFilterIndex(int index)
{
    if(filter.size() == 0)
        filterIndex = 0;
    else if(index >= (int)filter.size())
        filterIndex = filter.size() - 1;
    else
        filterIndex  = index;
}

String CommonDialog::getFileName()
{
    return fileName;
}

void CommonDialog::setFileName(String fileName)
{
    this->fileName = fileName;
}

String CommonDialog::getInitialDir()
{
    return initialDir;
}

CommonDialog::Options& CommonDialog::getOptions()
{
    return options;
}

void CommonDialog::setInitialDir(String initialDir)
{
    this->initialDir = initialDir;
}

String OpenDialog::getClassName()
{
    return "OpenDialog";
}

OpenDialog::OpenDialog()
{
    multiSelect = false;
    getOptions() += dlgOpt_fileMustExist;
    getOptions() += dlgOpt_pathMustExist;
}

void OpenDialog::setMultiSelect(bool enable)
{
    multiSelect = enable;
}

Strings& OpenDialog::getFiles()
{
    return files;
}

void OpenDialog::setFiles(char* szFiles)
{
    String dir, name;
    char * ptr;
    dir = szFiles;
    ptr = szFiles;
    ptr += dir.length() + 1;
    files.clear();
    if(ptr[0] == 0)
    {
        files.push_back(dir);
    }
    else
    {
        while(ptr[0] != 0)
        {
            name = ptr;
            files.push_back(dir + "\\" + name);
            ptr += name.length() + 1;
        }
    }
    if(files.size() > 0)
        setFileName(files[0]);
}

bool OpenDialog::execute()
{
    OPENFILENAME ofn;
    char* szFile;
    String filter;
    unsigned long int i, nMaxFile;
    bool result = false;

    prepare(ofn);
    if(multiSelect)
        nMaxFile = 65535;
    else
        nMaxFile = MAX_PATH;
    szFile = new char[nMaxFile];
    strcpy(szFile, getFileName().c_str());
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = nMaxFile;

    for(i = 0; i < getFilter().size(); i++)
        filter += getFilter()[i] + ";";
    if(filter == "")
        filter = "All files|*.*;";
    for(i = 0; i < filter.length(); i++)
    {
        if(filter[i] == '|' || filter[i] == ';')
            filter[i] = 0;
        else if(filter[i] == ',')
            filter[i] = ';';
    }
    ofn.lpstrFilter = filter.c_str();
    if(multiSelect)
        ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
    if(GetOpenFileName(&ofn))
    {
        if(multiSelect)
            setFiles(szFile);
        else
        {
            getFiles().clear();
            setFileName(szFile);
            getFiles().push_back(getFileName());
        }
        result = true;
    }
    delete[] szFile;
    return result;
}

SaveDialog::SaveDialog()
{
    getOptions() += dlgOpt_pathMustExist;
}

String SaveDialog::getClassName()
{
    return "SaveDialog";
}

String SaveDialog::getDefaultExt()
{
    return defExt;
}

void SaveDialog::setDefaultExt(String defaultExt)
{
    this->defExt = defaultExt;
}

bool SaveDialog::execute()
{
    OPENFILENAME ofn;
    char* szFile;
    String filter;
    unsigned long int i, nMaxFile;
    bool result = false;

    prepare(ofn);
    nMaxFile = MAX_PATH;
    szFile = new char[nMaxFile];
    strcpy(szFile, getFileName().c_str());
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = nMaxFile;

    for(i = 0; i < getFilter().size(); i++)
        filter += getFilter()[i] + ";";
    if(filter == "")
        filter = "All files|*.*;";
    for(i = 0; i < filter.length(); i++)
    {
        if(filter[i] == '|' || filter[i] == ';')
            filter[i] = 0;
        else if(filter[i] == ',')
            filter[i] = ';';
    }
    ofn.lpstrFilter = filter.c_str();
    ofn.lpstrDefExt = defExt.c_str();
    if(GetSaveFileName(&ofn))
    {
        setFileName(szFile);
        result = true;
    }
    delete[] szFile;
    return result;
}

