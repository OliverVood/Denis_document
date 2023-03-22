<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Base\Action;
	use Proj\Units\Consts;

	class Change extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function RegActionSelect():void { $this->select = new Action($this->name, 'select', "/{$this->name}/select?cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/select', {cid: %cid%}, Admin.General.Render.ToMain); return false;"); }
		protected function RegActionCreate(): void { $this->create = new Action($this->name, 'create', "/{$this->name}/create?cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/create', {cid: %cid%}, Admin.General.Render.ToMain); return false;"); }
		protected function RegActionUpdate(): void { $this->update = new Action($this->name, 'update', "/{$this->name}/update?id=%id%&cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%, cid: %cid%}, Admin.General.Render.ToMain); return false;"); }

		protected function Params(): array {
			return [
				'cid' => GetInt('cid')
			];
		}

		protected function Where($params): array {
			return [
				'`state` != ' . Consts\Changes::STATES['delete'],
				"`cid` = {$params['cid']}"
			];
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список актуального';
			$this->titleCreate = 'Добавить актуальное';
			$this->titleUpdate = 'Редактировать актуальное';

			$this->titleDoCreate = 'Актуальное добавлено';
			$this->titleDoUpdate = 'Актуальное изменено';
		}

		protected function NavigateSelect(): array { return [ function (array $params) { return $this->create->GetLink($this->titleCreate, ['cid' => $params['cid']]); } ]; }
		protected function NavigateCreate(): array { return [ function (array $params) { return $this->select->GetLink("<< {$this->titleSelect}", ['cid' => $params['cid']]); } ]; }
		protected function NavigateUpdate(): array { return [ function (array $params) { return $this->select->GetLink("<< {$this->titleSelect}", ['cid' => $params['cid']]); } ]; }

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->update->GetLink('Изменить', ['id' => $item['id'], 'cid' => $params['cid']]); },
				function (array $params, array $item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id'], 'cid' => $params['cid']]); }
			];
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id'		=> new Skins\Text('#'),
				'state'		=> new Skins\Text('Состояние'),
				'header'	=> new Skins\Text('Заголовок')
			];
		}

		protected function FieldsCreate(array $params): array {
			return [
				'cid' => ['skin' => 'hidden', 'name' => 'Список актуального', 'default' => $params['cid']],
				'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\News::STATES['draft']],
				'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
				'content' => ['skin' => 'textarea', 'name' => 'Текст', 'default' => ''],
				'cover' => ['skin' => 'file', 'name' => 'Обложка', 'default' => 'Выберите обложку', 'params' => ['accept' => '.jpg, .jpeg, .png']],
			];
		}

		protected function FieldsUpdate(array $params): array {
			return [
				'state' => ['skin' => 'select', 'name' => 'Состояние'],
				'header' => ['skin' => 'text', 'name' => 'Заголовок'],
				'content' => ['skin' => 'textarea', 'name' => 'Текст'],
				'cover' => ['skin' => 'file', 'name' => 'Обложка', 'params' => ['accept' => '.jpg, .jpeg, .png']],
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array &$data): void {
			$data['state'] = [
				Consts\Changes::STATE_DRAFT		=> 'Черновик',
				Consts\Changes::STATE_ACTIVE	=> 'Активная',
				Consts\Changes::STATE_INACTIVE	=> 'Не активная',
			];
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) unlink(Consts\Changes::PATH_COVER . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Changes::PATH_COVER;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}