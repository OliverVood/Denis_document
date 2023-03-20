<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/admin/views/group.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Site\Params;
	use Proj\Units\Consts;
	use Proj\DBObject;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Item;
	use Proj\Admin\Templates\General\Group;

	class General extends Units implements Consts\General {
		use Instance;

		private DBObject $db;

		public Action $site;
		public Action $out_head;
		public Action $out_menu;
		public Action $out_footer;
		public Action $db_struct;
		public Action $db_check;
		public Action $db_make;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->out_head 	= new Action();
			$this->out_menu 	= new Action();
			$this->out_footer 	= new Action();
			$this->site			= new Action('', '', '/');
			$this->db_struct 	= new Action('db', 'struct', '#', /** @lang JavaScript */ "console.log('struct'); return false;");
			$this->db_check 	= new Action('db', 'check', 'admin/db/check', /** @lang JavaScript */ "Base.Common.Query.Send('/db/check', Admin.General.Render.CheckDB); return false;");
			$this->db_make 		= new Action('db', 'make', 'admin/db/make', /** @lang JavaScript */ "Base.Common.Query.Send('/db/make', Admin.General.Render.CheckDB); return false;");

			Controller::instance()->view->Push($this->out_head, [$this, 'OutHead']);
			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
			Controller::instance()->view->Push($this->out_footer, [$this, 'OutFooter']);
			Controller::instance()->view->Push($this->db_check, [$this, 'Check']);
			Controller::instance()->view->Push($this->db_make, [$this, 'Make']);
		}

		public function OutHead() {
			Layout::instance()->header->Push("<div>Привет, " . USER_LOGIN . "</div>");
			Layout::instance()->header->Push(Users::instance()->exit->GetLink('', [], ['class' => 'logout']));
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(Item::object()->ToVar('<a href = "/" target = "_blank">Открыть сайт</a>'));
			Layout::instance()->menu->Push(
				Group::object()->ToVar('База данных', [
					$this->db_struct->GetLink('Структура'),
					$this->db_check->GetLink('Проверить')
				])
			);
		}

		public function OutFooter() {
			Layout::instance()->footer->Push('© ' . Params::$site_name);
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