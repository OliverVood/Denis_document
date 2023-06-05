<?php

	namespace Proj\Admin\Editor\Model;

	use Base\Action;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;

	trait Change {

		private function Init(): void {
			$this->params['cid'] = GetInt('cid');

			$this->titleSelect = 'Список актуального';
			$this->titleCreate = 'Добавить актуальное';
			$this->titleUpdate = 'Редактировать актуальное';
			$this->titleDelete = 'Удалить актуальное?';

			$this->querySelect
				->where('`state` != ' . Consts\Changes::STATE_DELETE)
				->where("`cid` = {$this->params['cid']}")
				->order('datecr', 'DESC')
				->order('id');
		}

		protected function RegActionSelect(): void { $this->select = new Action($this->name, 'select', "/{$this->name}/select?cid=%cid%&page=%page%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/select', {cid: %cid%, page: %page%}); return false;"); }
		protected function RegActionCreate(): void { $this->create = new Action($this->name, 'create', "/{$this->name}/create?cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/create', {cid: %cid%}); return false;"); }
		protected function RegActionUpdate(): void { $this->update = new Action($this->name, 'update', "/{$this->name}/update?id=%id%&cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%, cid: %cid%}); return false;"); }

		protected function RegActionDoDelete(): void { $this->do_delete = new Action($this->name, 'do_delete', "/{$this->name}/do_delete?id=%id%&cid=%cid%", /* @lang JavaScript */ "if (confirm('{$this->titleDelete}')) Base.Common.Query.SendData('/{$this->name}/do_delete', {id: %id%, cid: %cid%}); return false;"); }

		protected function NavigateSelect(): array { return [ function () { return $this->create->GetLinkHref($this->titleCreate, array_merge(['page' => 1], $this->params)); } ]; }

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHref('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHref('Удалить', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id'			=> new Browse\Text('#'),
				'state'			=> new Browse\ValueFromArray('Состояние', Consts\Changes::STATES_VIEW),
				'header'		=> new Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(): array {
			return [
				'cid'			=> new Edit\Hidden('Список актуального', 'form[cid]', $this->params['cid']),
				'state'			=> new Edit\Hidden('Состояние', 'form[state]', Consts\Changes::STATES['draft']),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'content'		=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'			=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'			=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Changes::STATE_DRAFT	=> 'Черновик',
					Consts\Changes::STATE_ACTIVE	=> 'Активный',
					Consts\Changes::STATE_INACTIVE	=> 'Не активный',
				]),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'content'		=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'			=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png')
			];
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

		private function DeleteCover($id): void {
			$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
			if ($old_file) unlink(Consts\Changes::PATH_COVER . $old_file);
		}

	}