<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/consts.inc';
	require 'views/group.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Proj\Admin\Templates\General\Item;
	use Proj\Units\Consts;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class General extends Units implements Consts\General {
		use Instance;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);

			Controller::PushScene('null', 'null', [$this, 'OutMenu'], [$this, 'OutMenu1'], [$this, 'OutMenu2']);
			Controller::PushScene('db', 'check', [$this, 'Check']);
			Controller::PushScene('1', '1', [$this, 'Check5']);
		}

		public function OutMenu() {//href = "admin?__p=db&__a=check"
			$items = [
				'<a href = "#">Структура</a>',
				'<a onclick = "Base.Common.RequestData(\'admin?__p=db&__a=check\');">Проверить</a>'
			];
			Layout::instance()->menu->Push(Group::object()->ToVar('База данных', $items));
		}

		public function OutMenu1() {
			Layout::instance()->menu->Push(Item::object()->ToVar('<a href = "#">Раздел меню</a>'));
		}

		public function OutMenu2() {
			Layout::instance()->menu->Push(Item::object()->ToVar('<a href = "#">Ну очень-очень длинный раздел меню</a>'));
		}

		public function Check() {
//			$t = $db->Check();
//			SendJSONData($t);
			SendJSONData([1,2,3,4,5]);
		}

		public function Check5() {
			Layout::instance()->main->Push('sdfhgdyfdsyfg');
		}

	}

	General::init();