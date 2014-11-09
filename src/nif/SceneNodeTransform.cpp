#include "SceneNodeTransform.hpp"

SceneNodeTransform::SceneNodeTransform(NiAVObjectRef node) : SceneNode(node) {

    //
    // "transform": {
    //    "frequency": transform->GetFrequency(),
    //    "phase": transform->GetPhase(),
    //    "start": transform->GetStartTime(),
    //    "stop": transform->GetStopTime(),
    //    "type": {
    //       "translate": "LINEAR_KEY",

    //       "rotate": "QUADRATIC_KEY",        -> quaternion rotation type

    //       "rotate": {                       -> if instanceof Object -> euler rotation type
    //          "x": "LINEAR_KEY",
    //          "y": "LINEAR_KEY",
    //          "z": "QUADRATIC_KEY"
    //       }

    //       "scale": "LINEAR_KEY"
    //    },
    //    "keys": [
    //       {
    //          "time": 0,
    //          "pos": [1, 1, 1],        // additional
    //          "rotq": [1, 0, 0, 0],    // additional
    //          "rot": [0, 0, 0],        // additional
    //          "scl": 1                 // additional
    //       }, ...
    //    ]
    // }
    //

    // FUTURE: implement euler rotation and quaternion rotation
    // TODO: check if target is parent NiNode
    // TODO: use own class SceneNodeTransform
    list<NiTimeControllerRef> controllers = node->GetControllers();

    while (!controllers.empty()) {

        NiTimeControllerRef controller = controllers.front();
        controllers.pop_front();

        if (controller->IsDerivedType(NiTransformController::TYPE)) {

            NiTransformControllerRef transform = DynamicCast<NiTransformController>(controller);

            this->node["transform"]["frequency"] = transform->GetFrequency();  // 1.0 means that the times in the controller are already in seconds
            this->node["transform"]["phase"] = transform->GetPhase();   // This is used to map the time indices stored in the controller
            // to seconds. The value is added to the result of the multiplication
            // of application time by frequency to arrive at the controller time,
            // so the default value of 0.0 means that there is no phase shift in the time indices.

            this->node["transform"]["start"] = transform->GetStartTime();
            this->node["transform"]["stop"] = transform->GetStopTime();

            //cout << "TARGET: " << transform->GetTarget()->GetIDString() << endl;

            NiTransformInterpolatorRef interpolator = DynamicCast<NiTransformInterpolator>(transform->GetInterpolator());
            NiTransformDataRef keyframes = interpolator->GetData();

            //enum KeyType {
            //    LINEAR_KEY = 1, /*!< Use linear interpolation. */
            //            QUADRATIC_KEY = 2, /*!< Use quadratic interpolation.  Forward and back tangents will be stored. */
            //            TBC_KEY = 3, /*!< Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored. */
            //            XYZ_ROTATION_KEY = 4, /*!< For use only with rotation data.  Separate X, Y, and Z keys will be stored instead of using quaternions. */
            //            CONST_KEY = 5, /*!< Step function. Used for visibility keys in NiBoolData. */
            //};

            if (keyframes->GetRotateType() == XYZ_ROTATION_KEY) {

                cout << "XYZ ROTATION" << endl;

                switch (keyframes->GetXRotateType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["rotate"]["x"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["rotate"]["x"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetXRotateType() << endl;
                        throw exception();
                }

                switch (keyframes->GetZRotateType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["rotate"]["y"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["rotate"]["y"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetZRotateType() << endl;
                        throw exception();
                }

                switch (keyframes->GetYRotateType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["rotate"]["z"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["rotate"]["z"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetYRotateType() << endl;
                        throw exception();
                }

                vector<Key<float>> xRotates = keyframes->GetXRotateKeys();
                vector<Key<float>> yRotates = keyframes->GetYRotateKeys();
                vector<Key<float>> zRotates = keyframes->GetZRotateKeys();

                this->node["transform"]["rotateKeysX"] = arrayValue;
                this->node["transform"]["rotateKeysY"] = arrayValue;
                this->node["transform"]["rotateKeysZ"] = arrayValue;

                for (auto & key : xRotates) {

                    Value data;

                    data["time"] = key.time;

                    data["rot"] = key.data;

                    this->node["transform"]["rotateKeysX"].append(data);
                }

                for (auto & key : zRotates) {

                    Value data;

                    data["time"] = key.time;

                    data["rot"] = key.data;

                    this->node["transform"]["rotateKeysY"].append(data);
                }

                for (auto & key : yRotates) {

                    Value data;

                    data["time"] = key.time;

                    data["rot"] = key.data;

                    this->node["transform"]["rotateKeysZ"].append(data);
                }

            } else {

                cout << "QUATERNION ROTATION" << endl;

                switch (keyframes->GetRotateType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["rotate"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["rotate"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetRotateType() << endl;
                        throw exception();
                }

                vector<Key<Quaternion>> quaternions = keyframes->GetQuatRotateKeys();

                this->node["transform"]["rotateKeys"] = arrayValue;

                for (auto & key : quaternions) {

                    Value data;

                    data["time"] = key.time;

                    data["rot"][0] = key.data.x;
                    data["rot"][1] = key.data.z;
                    data["rot"][2] = -key.data.y;
                    data["rot"][3] = key.data.w;

                    this->node["transform"]["rotateKeys"].append(data);
                }
            }

            vector<Key<Vector3>> translates = keyframes->GetTranslateKeys();
            vector<Key<float>> scales = keyframes->GetScaleKeys();

            if (translates.size() > 0) {

                switch (keyframes->GetTranslateType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["translate"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["translate"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetTranslateType() << endl;
                        throw exception();
                }

                cout << "TRANSLATE : " << keyframes->GetTranslateType() << endl;

                this->node["transform"]["translateKeys"] = arrayValue;

                for (auto & key : translates) {

                    Value data;

                    data["time"] = key.time;

                    data["pos"][0] = key.data.x;
                    data["pos"][1] = key.data.z;
                    data["pos"][2] = -key.data.y;

                    this->node["transform"]["translateKeys"].append(data);
                }
            }

            if (scales.size() > 0) {

                switch (keyframes->GetScaleType()) {

                    case LINEAR_KEY: // Use linear interpolation.
                        this->node["transform"]["type"]["scale"] = "LINEAR";
                        break;
                    case QUADRATIC_KEY: // Use quadratic interpolation.  Forward and back tangents will be stored.
                        this->node["transform"]["type"]["scale"] = "QUADRATIC";
                        break;
                    case TBC_KEY: // Use Tension Bias Continuity interpolation.  Tension, bias, and continuity will be stored.
                    case CONST_KEY: // Step function. Used for visibility keys in NiBoolData.
                    default:
                        cerr << keyframes->GetScaleType() << endl;
                        throw exception();
                }

                cout << "SCALE : " << keyframes->GetScaleType() << endl;

                this->node["transform"]["scaleKeys"] = arrayValue;

                for (auto & key : scales) {

                    Value data;

                    data["time"] = key.time;
                    data["scl"] = key.data;

                    this->node["transform"]["scaleKeys"].append(data);
                }
            }
        }
    }
}