<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'general/general.consts.inc';

	use Base\Access;
	use Base\Action;
	use Base\ActionOutside;
	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class General extends UnitAccess implements Consts\General {
		public static Action $out_head;
		public static Action $out_menu;
		public static Action $out_footer;
		public static Action $home;
		public static Action $db_structure;
		public static Action $db_check;
		public static Action $db_make;

		public static ActionOutside $site;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		protected function RegAccess(): void {
			Access::AddCollection($this->id, $this->name, 'Основное (единица)');
			Access::AddRight($this->id, self::ACCESS_SETTING, 'setting', 'Назначение прав');
			Access::AddRight($this->id, self::ACCESS_DB_CHECK, 'check', 'Проверить БД');
			Access::AddRight($this->id, self::ACCESS_DB_MAKE, 'make', 'Исправить БД');
			Access::AddRight($this->id, self::ACCESS_DB_STRUCTURE, 'structure', 'Структура БД');
		}

		public static function RegActions() {
			self::$out_head		= new Action('always', 'always');
			self::$out_menu		= new Action('always', 'always');
			self::$out_footer	= new Action('always', 'always');
			self::$home			= new Action('null', 'null', 'default', /** @lang JavaScript */ "Base.Common.Query.Send(''); return false;");
			self::$db_structure	= new Action('db', 'structure', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/db/structure'); return false;");
			self::$db_check		= new Action('db', 'check', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/db/check', Admin.General.Render.CheckDB); return false;");
			self::$db_make		= new Action('db', 'make', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/db/make', Admin.General.Render.CheckDB); return false;");

			self::$site			= new ActionOutside('/', '');
		}

	}

	General::RegActions();