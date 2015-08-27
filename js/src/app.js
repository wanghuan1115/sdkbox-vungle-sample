
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        this._super();
        this._coin = 0;
        var self = this;

        var size = cc.winSize;

        var ui = ccs.load(res.MainScene_json);
        this.addChild(ui.node);

        this.btnVideo = ui.node.getChildByName("btnVideo");
        this.btnVideo.setEnabled(false);
        this.btnVideo.addClickEventListener(function(){
            sdkbox.PluginVungle.show("video");
        });

        this.btnReward = ui.node.getChildByName("btnReward");
        this.btnReward.setEnabled(false);
        this.btnReward.addClickEventListener(function(){
            sdkbox.PluginVungle.show("reward");
        });

        this._txtCoins = ui.node.getChildByName("txtCoins");

        sdkbox.PluginVungle.init();
        sdkbox.PluginVungle.setListener({
            onVungleCacheAvailable : function () {
                self.btnVideo.setEnabled(true);
                self.btnReward.setEnabled(true);
            },
            onVungleAdViewed : function (isComplete) {
                if (isComplete) {
                    cc.log("Complete");
                }
                else {
                    cc.log("Not Complete");
                }

            },
            onVungleStarted : function () {
                cc.log("Ad Started");
            },
            onVungleFinished : function () {
                cc.log("Ad Finished");
            },
            onVungleAdReward : function (name){
                cc.log("Ad Reward");
                self._coin ++;
                self._txtCoins.setString(self._coin);
            }
        });

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

