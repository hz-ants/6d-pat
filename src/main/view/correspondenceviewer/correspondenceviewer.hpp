#ifndef CORRESPONDENCEEDITOR_H
#define CORRESPONDENCEEDITOR_H

#include "model/image.hpp"
#include "model/objectmodel.hpp"
#include "model/correspondence.hpp"
#include "model/modelmanager.hpp"
#include "rendering/correspondenceviewerglwidget.hpp"

#include <QList>
#include <QMap>
#include <QWidget>
#include <QSignalMapper>
#include <QScopedPointer>
#include <QtAwesome.h>
#include <QTimer>

namespace Ui {
class CorrespondenceViewer;
}

/*!
 * \brief The CorrespondenceEditor class holds the image that is to be annotated and allows
 * adding ObjectModels and place them at specific spots. It does NOT allow diret editing.
 * This is what the CorrespondenceEditorControls are for.
 */
class CorrespondenceViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CorrespondenceViewer(QWidget *parent = 0, ModelManager* modelManager = 0);
    ~CorrespondenceViewer();
    /*!
     * \brief setModelManager sets the model manager that this correspondence editor uses.
     * The model manager is expected to not be null.
     * \param modelManager the manager to be set, must not be null
     */
    void setModelManager(ModelManager* modelManager);

public Q_SLOTS:
    /*!
     * \brief setImage sets the image that this CorrespondenceEditor displays.
     * \param index the index of the image to be displayed
     */
    void setImage(Image *image);

    /*!
     * \brief reset resets the view to display nothing.
     */
    void reset();

    void reloadCorrespondences();

    /*!
     * \brief visualizeLastClickedPosition draws a point at the position that the user last clicked.
     * The color is retrieved using the provided index from the DisplayHelper.
     * \param correspondencePointIndex the index of the correspondence point, e.g. 1 if it is the
     * second time the user clicked the image to create a correspondence
     */
    void visualizeLastClickedPosition(int correspondencePointIndex);

    /*!
     * \brief onCorrespondenceCreationAborted reacts to the signal indicating that the process
     * of creating a new correspondence was aborted by the user.
     */
    void onCorrespondenceCreationAborted();

    /*!
     * \brief removePositionVisualizations removes all visualized points from the image.
     */
    void removePositionVisualizations();

    /*!
    * \brief onCorrespondencePointFinished is the slot that handles whenever the user wants to create
    * a correspondence point that consists of a 2D location and a 3D point on the object model.
    * \param point2D the 2D point on the image
    * \param currentNumberOfPoints the current number of correspondence points
    * \param minimumNumberOfPoints the total number required to be able to create an actual ObjectImage Correspondence
    */
    void onCorrespondencePointStarted(QPoint, int currentNumberOfPoints, int);

    void onCorrespondenceUpdated(Correspondence *correspondence);

    /*!
     * \brief onOpacityForObjectModelsChanged slot for when the opacity of the object models is changed.
     * \param opacity the new opacity of the object models that are displayed
     */
    void onOpacityChangeStarted(int opacity);

    void onOpacityChangeEnded();

Q_SIGNALS:
    /*!
     * \brief imageClicked Q_EMITted when the displayed image is clicked anywhere
     */
    void imageClicked(Image *image, QPoint position);
    /*!
     * \brief correspondenceClicked Q_EMITted when a displayed object model is clicked
     */
    void correspondenceClicked(Correspondence *correspondence);

private:

    Ui::CorrespondenceViewer *ui;
    QtAwesome* awesome;
    ModelManager* modelManager;

    // All necessary stuff for 3D
    qreal objectsOpacity = 1.f;
    QTimer *opacityTimer = 0;

    // Store the last clicked position, so that we can visualize it if the user calls the respective
    // function.
    QPoint lastClickedPosition;
    QScopedPointer<Image> currentlyDisplayedImage;

    // Stores, whether we are currently looking at the "normal" image, or the (maybe present)
    // segmentation image
    bool showingNormalImage = true;

    void connectModelManagerSlots();

private Q_SLOTS:
    /*!
     * \brief showSegmentationImage is there for the switch view button
     */
    void switchImage();
    void resetPositionOfGraphicsView();
    void onImageClicked(QPoint point);
    // Private slot listening to model manager
    void onCorrespondenceDeleted(const QString &id);
    void onCorrespondenceAdded(const QString &id);
    void onCorrespondencesChanged();
    void onImagesChanged();
    void onObjectModelsChanged();
    void updateOpacity();
};

#endif // CORRESPONDENCEEDITOR_H
