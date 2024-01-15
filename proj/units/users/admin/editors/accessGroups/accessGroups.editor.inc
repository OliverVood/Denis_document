<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'users/admin/editors/accessGroups/accessGroups.editor.model.inc';
	require DIR_UNITS . 'users/admin/editors/accessGroups/views/update.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Access;
	use Base\ActionRight;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Helper\Response;
	use Proj\Templates\Editor\AccessGroups as TPL;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units;

	class AccessGroups extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список прав группы';
			$this->titleUpdate = 'Редактирование прав группы';
			$this->titleDoUpdate = 'Права группы установлены';

			$this->model = new Model\AccessGroups($table, $this->params);
		}

		protected function RegAccess() {
			$this->AddCollection();
			$this->AddRight(self::ACCESS_SETTING, 'setting', 'Назначение прав');
			$this->AddRight(self::ACCESS_UPDATE, 'update', 'Изменение');
		}

		protected function RegActionUpdate(): void { $this->update = new ActionRight($this->id, $this->name, 'update', "/{$this->name}/update?gid=%gid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {gid: %gid%}); return false;"); }
		protected function RegActionDoUpdate(): void { $this->do_update = new ActionRight($this->id, $this->name, 'do_update', "/{$this->name}/do_update?gid=%gid%", /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this); return false;"); }

		protected function NavigateUpdate(): array { return [ function () { return Units\Users::instance()->editor_groups->select->GetLinkHref('<< ' . Units\Users::instance()->editor_groups->titleSelect, array_merge(['page' => 1], $this->params)); } ]; }

		#[NoReturn] protected function OnUpdate(): void {
			if (!Access::Allow(self::ACCESS_UPDATE, $this->id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$gid = GetInt('gid');

			$rights = Access::GetRights();
			$items = $this->model->GetAccessGroup($gid);

			$navigate			= $this->NavigateUpdate();

			Response::PushHistory($this->update, array_merge(['gid' => $gid], $this->params));
			Response::PushSection('main', TPL\Update::ToVar($this, $gid, $rights, $items, "{$this->titleUpdate} #{$gid}", $navigate)/*, $this->params*/);
			Response::SendJSON();
		}

		#[NoReturn] protected function DoUpdate(): void {
			if (!Access::Allow(self::ACCESS_UPDATE, $this->id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$gid = GetInt('gid');
			$rights = GetParam('rights', []);

			$this->model->UpdateAccess($rights, $gid);

			Response::PushNoticeOk($this->titleDoUpdate);
			Response::SendJSON();
		}

	}