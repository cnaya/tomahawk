#ifndef SOURCETREEVIEW_H
#define SOURCETREEVIEW_H

#include <QTreeView>
#include <QMenu>

#include "source.h"

class CollectionModel;
class PlaylistModel;
class SourcesModel;

class SourceTreeView : public QTreeView
{
Q_OBJECT

public:
    explicit SourceTreeView( QWidget* parent = 0 );

signals:
    void onOnline( const QModelIndex& index );
    void onOffline( const QModelIndex& index );

private slots:
    void onItemActivated( const QModelIndex& index );
    void onSelectionChanged();

    void loadPlaylist();
    void deletePlaylist();
    void renamePlaylist();
    
    void onCustomContextMenu( const QPoint& pos );
    void onSourceOffline( Tomahawk::source_ptr );

protected:
    void drawBranches( QPainter* painter, const QRect& rect, const QModelIndex& index ) const {}
    void drawRow( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;

    virtual void paintEvent( QPaintEvent* event );

    virtual void dragEnterEvent( QDragEnterEvent* event );
    virtual void dragLeaveEvent( QDragLeaveEvent* event ) { m_dragging = false; setDirtyRegion( m_dropRect ); }
    virtual void dragMoveEvent( QDragMoveEvent* event );
    virtual void dropEvent( QDropEvent* event );

private:
    void setupMenus();

    CollectionModel* m_collectionModel;
    SourcesModel* m_model;
    QModelIndex m_contextMenuIndex;

    QMenu m_playlistMenu;
    QAction* m_loadPlaylistAction;
    QAction* m_renamePlaylistAction;
    QAction* m_deletePlaylistAction;

    bool m_dragging;
    QRect m_dropRect;
};

#endif // SOURCETREEVIEW_H
