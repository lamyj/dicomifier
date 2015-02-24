#include "ResultsTreeModel.h"

namespace dicomifier
{

namespace gui
{

ResultsTreeModel
::ResultsTreeModel(QObject *parent):
    QAbstractItemModel(parent),
    _rootItem(NULL)
{
    this->_rootItem = new TreeItem();

    QList<QVariant> rootData;
    rootData << "Name" << "DICOM" << "Store" << "DICOMDIR" << "ZIP";
    this->_rootItem->set_data(rootData);
}

ResultsTreeModel
::~ResultsTreeModel()
{
    if (this->_rootItem != NULL)
    {
        delete this->_rootItem;
        this->_rootItem = NULL;
    }
}

void
ResultsTreeModel
::Initialize(std::vector<TreeItem *> dataList,
             std::map<std::string, GenerationResultItem> results)
{
    this->_datalist = dataList;

    // Sort data
    std::map<std::string, std::map<std::string, std::map<std::string, std::vector<TreeItem*> > > > sorteddata;
    for (auto iterdata : this->_datalist)
    {
        std::string name = iterdata->get_name();
        if (sorteddata.find(name) == sorteddata.end())
        {// create new entry (Subject)
            std::map<std::string, std::map<std::string, std::vector<TreeItem*> > > subjectmap;
            sorteddata[name] = subjectmap;
        }

        std::string study = iterdata->get_study();
        if (sorteddata[name].find(study) == sorteddata[name].end())
        {// create new entry (Study)
            std::map<std::string, std::vector<TreeItem*> > studymap;
            sorteddata[name][study] = studymap;
        }

        std::string series = iterdata->get_series();
        if (sorteddata[name][study].find(series) == sorteddata[name][study].end())
        {// create new entry (Series)
            sorteddata[name][study][series] = {};
        }

        sorteddata[name][study][series].push_back(iterdata);
    }

    // Display data

    for (auto itersubject = sorteddata.begin();
         itersubject != sorteddata.end();
         itersubject++)
    {
        // Create Subject
        TreeItem * itemSubject = new TreeItem(this->_rootItem);
        itemSubject->set_name(itersubject->first);

        bool subjectstatus = true;
        bool subjectstorestatus = true;
        bool storerequested = false;

        // Create sub-item
        for (auto iterstudy = itersubject->second.begin();
             iterstudy != itersubject->second.end();
             iterstudy++)
        {
            // Create Study
            TreeItem * itemStudy = new TreeItem(itemSubject);
            itemStudy->set_study(iterstudy->first);

            bool studystatus = true;
            bool studystorestatus = true;

            // Create sub-item
            for (auto iterseries = iterstudy->second.begin();
                 iterseries != iterstudy->second.end();
                 iterseries++)
            {
                // Create Series
                TreeItem * itemSeries = new TreeItem(itemStudy);
                itemSeries->set_series(iterseries->first);

                bool seriesstatus = true;
                bool seriesstorestatus = true;

                // Create sub-item
                for (auto iterReco : iterseries->second)
                {
                    // Create Reconstruction
                    TreeItem * itemReco = new TreeItem(itemSeries, iterReco);

                    QString dicommsg;
                    QString storemsg = QString("Fail");
                    if (itemReco->get_DicomErrorMsg() == "" || itemReco->get_DicomErrorMsg() == "OK")
                    {
                        dicommsg = QString("OK");

                        storerequested |= itemReco->get_StoreErrorMsg() != "";

                        if (itemReco->get_StoreErrorMsg() == "" || itemReco->get_StoreErrorMsg() == "OK")
                        {
                            storemsg = QString(itemReco->get_StoreErrorMsg().c_str());
                        }
                        else
                        {
                            storemsg = QString("Fail");
                            seriesstorestatus = false;
                        }
                    }
                    else if (itemReco->get_DicomErrorMsg() == "Canceled")
                    {
                        dicommsg = QString("Canceled");
                        storemsg = QString("Canceled");
                        seriesstatus = false;
                        seriesstorestatus = false;
                    }
                    else
                    {
                        dicommsg = QString("Fail");
                        seriesstatus = false;
                        seriesstorestatus = false;
                    }

                    // set reconstruction data
                    QList<QVariant> itemRecoData;
                    itemRecoData << QString(itemReco->get_reconstruction().c_str());
                    itemRecoData << dicommsg;
                    itemRecoData << storemsg;
                    itemRecoData << "";
                    itemRecoData << "";
                    itemReco->set_data(itemRecoData);

                    // Append reconstruction in series
                    itemSeries->appendChild(itemReco);
                }

                itemSeries->set_DicomErrorMsg("");

                // set series data
                QString dicommsg = seriesstatus ? QString("OK") : QString("Fail");
                QString storemsg = !storerequested ? QString("") : seriesstorestatus ? QString("OK") :
                                                                                       QString("Fail");
                QList<QVariant> itemSeriesData;
                itemSeriesData << QString(itemSeries->get_series().c_str());
                itemSeriesData << dicommsg;
                itemSeriesData << storemsg;
                itemSeriesData << "";
                itemSeriesData << "";
                itemSeries->set_data(itemSeriesData);

                // Append series in study
                itemStudy->appendChild(itemSeries);

                studystatus &= seriesstatus;
                studystorestatus &= seriesstorestatus;
            }

            itemStudy->set_DicomErrorMsg("");
            itemStudy->set_StoreErrorMsg("");

            // set study data
            QString dicommsg = studystatus ? QString("OK") : QString("Fail");
            QString storemsg = !storerequested ? QString("") : studystorestatus ? QString("OK") :
                                                                                  QString("Fail");
            QList<QVariant> itemStudyData;
            itemStudyData << QString(itemStudy->get_study().c_str());
            itemStudyData << dicommsg;
            itemStudyData << storemsg;
            itemStudyData << "";
            itemStudyData << "";
            itemStudy->set_data(itemStudyData);

            // Append study in subject
            itemSubject->appendChild(itemStudy);

            subjectstatus &= studystatus;
            subjectstorestatus &= studystorestatus;
        }

        itemSubject->set_DicomErrorMsg("");
        itemSubject->set_StoreErrorMsg("");
        itemSubject->set_DicomdirErrorMsg(results[itemSubject->get_name()].get_DicomdirErrorMsg());
        itemSubject->set_ZipErrorMsg(results[itemSubject->get_name()].get_ZipErrorMsg());

        // set subject data
        QString dicommsg = subjectstatus ? QString("OK") : QString("Fail");
        QString storemsg = !storerequested ? QString("") : subjectstorestatus ? QString("OK") :
                                                                                QString("Fail");
        QList<QVariant> itemSubjectData;
        itemSubjectData << QString(itemSubject->get_name().c_str());
        itemSubjectData << dicommsg;
        itemSubjectData << storemsg;
        itemSubjectData << QString(results[itemSubject->get_name()].get_dicomdirCreationToString().c_str());
        itemSubjectData << QString(results[itemSubject->get_name()].get_zipCreationToString().c_str());
        itemSubject->set_data(itemSubjectData);

        // Append Subject in Tree
        this->_rootItem->appendChild(itemSubject);
    }
}

QVariant
ResultsTreeModel
::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    switch (role)
    {
    case Qt::CheckStateRole:
    {
        break;
    }
    case Qt::DisplayRole:
    {
        return item->data(index.column());
    }
    case Qt::SizeHintRole:
    {
        return QSize(100,40);
    }
    case Qt::ForegroundRole:
    {
        if (index.column() != 0)
        {
            if (item->data(index.column()).toString() == QString("OK"))
            {
                return QBrush(QColor(10, 220, 30));
            }
            else if (item->data(index.column()).toString() == QString("Fail"))
            {
                return QBrush(QColor(220, 0, 0));
            }
        }
        return QBrush(QColor(0, 0, 0));
    }
    case Qt::ToolTipRole:
    {
        if (index.column() == 0)
        {
            break;
        }
        else if (index.column() == 1)
        {
            if (item->get_DicomErrorMsg() != "" && item->get_DicomErrorMsg() != "OK")
            {
                return QString(item->get_DicomErrorMsg().c_str());
            }
        }
        else if (index.column() == 2)
        {
            if (item->get_StoreErrorMsg() != "" && item->get_StoreErrorMsg() != "OK")
            {
                return QString(item->get_StoreErrorMsg().c_str());
            }
        }
        else if (index.column() == 3)
        {
            if (item->get_DicomdirErrorMsg() != "")
            {
                return QString(item->get_DicomdirErrorMsg().c_str());
            }
        }
        else if (index.column() == 4)
        {
            if (item->get_ZipErrorMsg() != "")
            {
                return QString(item->get_ZipErrorMsg().c_str());
            }
        }
    }
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags
ResultsTreeModel
::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (! item->isEnabled())
    {
        return Qt::ItemIsUserCheckable;
    }

    // Items are selectable
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}

QVariant
ResultsTreeModel
::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return this->_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex
ResultsTreeModel
::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem * parentItem;

    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex
ResultsTreeModel
::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem * childItem =
            static_cast<TreeItem*>(index.internalPointer());
    TreeItem * parentItem = childItem->parent();

    if (parentItem == this->_rootItem)
    {
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(), 0, parentItem);
}

int
ResultsTreeModel
::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    TreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int
ResultsTreeModel
::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    }

    return this->_rootItem->columnCount();
}

} // namespace gui

} // namespace dicomifier
