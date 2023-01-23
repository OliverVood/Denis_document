<?php

	namespace Base\Templates\HTML\Element;

	class Form {
		private array $data;

		public function __construct(array $data = []) {
			$this->data = $data;
		}

		public function Begin(string $action = ''): void { ?>
			<form action = "<?= $action; ?>">
		<?php }

		public function End(): void { ?>
			</form>
		<?php }

		public function Submit(string $value = 'Отправить'): void { ?>
			<input type = "submit" value = "<?= $value; ?>" onclick = "Base.Common.Query.SubmitForm(this, (data) => { console.log(data); }); return false;">
		<?php }

		public function Element(string $skin, string $name, string | int $value, array $params = []): void {
			switch ($skin) {
				case 'text': Text::object()->Render($name, $value, $params); break;
				case 'select': Select::object()->Render($name, $value, $this->data[$name] ?? [], $params); break;
				case 'textarea': Textarea::object()->Render($name, $value, $params); break;
				default: echo 'ELEMENT NOT FOUND'; break;
			}
		}

	}