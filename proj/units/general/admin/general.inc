<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/consts.inc';
	require 'views/group.tpl';


	use JetBrains\PhpStorm\NoReturn;

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DB;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Item;
	use Proj\Admin\Templates\General\Group;

	class General extends Units implements Consts\General {
		use Instance;

		private DB $db;

		private Action $out_menu;
		private Action $db_struct;
		private Action $db_check;
		private Action $db_make;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DB::instance();

			$this->out_menu 	= new Action();
			$this->db_struct 	= new Action('db', 'struct', '#', /** @lang JavaScript */ "console.log('struct'); return false;");
			$this->db_check 	= new Action('db', 'check', 'admin/db/check', /** @lang JavaScript */ "Base.Common.Query.Send('/db/check', Admin.General.Render.CheckDB); return false;");
			$this->db_make 		= new Action('db', 'make', 'admin/db/make', /** @lang JavaScript */ "Base.Common.Query.Send('/db/make', Admin.General.Render.CheckDB); return false;");

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu'], [$this, 'OutMenu1'], [$this, 'OutMenu2']);
			Controller::instance()->view->Push($this->db_check, [$this, 'Check']);
			Controller::instance()->view->Push($this->db_make, [$this, 'Make']);
		}

		public function OutMenu() {
			$items = [
				$this->db_struct->GetLink('Структура'),
				$this->db_check->GetLink('Проверить')
			];
			Layout::instance()->menu->Push(Group::object()->ToVar('База данных', $items));
		}

		public function OutMenu1() {
			Layout::instance()->menu->Push(Item::object()->ToVar('<a href = "#">Раздел меню</a>'));

			Layout::instance()->header->Push('Привет, админ');
			Layout::instance()->footer->Push('с Documents');
		}

		public function OutMenu2() {
			Layout::instance()->menu->Push(Item::object()->ToVar('<a href = "#">Ну очень-очень длинный раздел меню</a>'));
		}

		#[NoReturn] public function Check() {
			SendJSONSuccess($this->db->Check());
		}

		#[NoReturn] public function Make() {
			$this->db->Make();
			SendJSONSuccess($this->db->Check());
		}

	}

	General::init();