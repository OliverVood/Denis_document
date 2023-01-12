<?php

	namespace Proj\Admin\Units;

	require 'statisticsEditor.inc';
	require DIR_UNITS . 'statistics/consts.inc';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	//	use Proj\DB;
	use Proj\Admin\Editors\StatisticsEditor;
	use Proj\Admin\Templates\Layout;
//	use Proj\Admin\Templates\General\Item;
	use Proj\Admin\Templates\General\Group;

	class Statistics extends Units implements Consts\Statistics {
		use Instance;

		private StatisticsEditor $editor;
//		private DB $db;
//
//		private Action $site;
//		private Action $out_head;
		private Action $out_menu;
//		private Action $out_footer;
//		private Action $db_struct;
//		private Action $db_check;
//		private Action $db_make;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->editor = new StatisticsEditor(self::NAME);
//			$this->db = DB::instance();
//
//			$this->out_head 	= new Action();
			$this->out_menu 	= new Action();
//			$this->out_footer 	= new Action();
//			$this->site			= new Action('', '', '/');
//			$this->db_struct 	= new Action('db', 'struct', '#', /** @lang JavaScript */ "console.log('struct'); return false;");
//			$this->db_check 	= new Action('db', 'check', 'admin/db/check', /** @lang JavaScript */ "Base.Common.Query.Send('/db/check', Admin.General.Render.CheckDB); return false;");
//			$this->db_make 		= new Action('db', 'make', 'admin/db/make', /** @lang JavaScript */ "Base.Common.Query.Send('/db/make', Admin.General.Render.CheckDB); return false;");
//
//			Controller::instance()->view->Push($this->out_head, [$this, 'OutHead']);
			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
//			Controller::instance()->view->Push($this->out_footer, [$this, 'OutFooter']);
//			Controller::instance()->view->Push($this->db_check, [$this, 'Check']);
//			Controller::instance()->view->Push($this->db_make, [$this, 'Make']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Статистика', [
					$this->editor->select->GetLink('Показать')
				])
			);
		}

	}

	Statistics::init();